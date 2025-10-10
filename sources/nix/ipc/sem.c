/*
 * SystemV IPC semaphore functions for libnix-amiga
 * 
 * This implementation is based on Peter Bengtsson's sysvipc implementation
 */

#include <sys/sem.h>
#include <sys/ipc.h>
#include <errno.h>
#include <string.h>
#include <exec/exec.h>
#include <dos/dos.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <proto/exec.h>
#include "ipcprivate.h"

extern struct ExecBase *SysBase;

/* Forward declarations for IPC functions */
extern struct IPCIdKeyMap *__get_semcx(void);
extern void *GetIPCById(struct IPCIdKeyMap *m, int id);
extern void IPCLock(struct IPCIdKeyMap *m);
extern void IPCUnlock(struct IPCIdKeyMap *m);
extern void IPCRmId(struct IPCIdKeyMap *m, int id, void (*Destroy)(struct IPCGeneric *));

/* Forward declarations for local structures */
struct semid_ds_local {
	struct IPCGeneric	generic;	/* Must be first for IPCGeneric compatibility */
	struct sem	*sem_base;	/* Pointer to first semaphore in set */
	unsigned short	sem_nsems;	/* Number of semaphores in set */
	time_t		sem_otime;	/* Last semop time */
	time_t		sem_ctime;	/* Last change time */
};

/* Construct semaphore set */
static struct semid_ds_local *sem_construct(int key, int flags)
{
	struct semid_ds_local *si;
	
	si = AllocVec(sizeof(struct semid_ds_local), MEMF_ANY|MEMF_CLEAR);
	if (si) {
		si->sem_base = NULL;
		si->generic.perm.mode = flags & 0777;
		si->generic.perm.key = key;
		si->sem_nsems = 0;
		si->sem_ctime = time(NULL);
	}
	return si;
}

/* Destroy semaphore set */
static void sem_destroy(struct semid_ds_local *si)
{
	if (si) {
		if (si->sem_base) {
			FreeVec(si->sem_base);
		}
		FreeVec(si);
	}
}

/* Setup individual semaphore */
static void sem_setup(struct sem *s)
{
	s->semval = 1;
	s->sempid = 0;
	s->semncnt = 0;
	s->semzcnt = 0;
}

/* Get semaphore set by ID */
static struct semid_ds_local *GetSemById(int id)
{
	return (struct semid_ds_local *)GetIPCById(__get_semcx(), id);
}

/* Create or get semaphore set */
int semget(key_t key, int nsems, int semflg)
{
	int id = -1;
	int i;
	struct sem *sa;
	struct semid_ds_local *si;
	struct IPCIdKeyMap *semcx = __get_semcx();

	if (nsems <= 0 || nsems > 250) {
		errno = EINVAL;
		return -1;
	}

	IPCLock(semcx);

	/* Simple implementation - always create new if not found */
	for (i = 0; i < semcx->nobj; i++) {
		if (semcx->objv[i]) {
			si = (struct semid_ds_local *)semcx->objv[i];
			if (si->generic.perm.key == key) {
				if (semflg & IPC_CREAT && semflg & IPC_EXCL) {
					errno = EEXIST;
					break;
				}
				id = i;
				break;
			}
		}
	}

	if (id == -1 && (semflg & IPC_CREAT)) {
		/* Create new semaphore set */
		si = sem_construct(key, semflg);
		if (si) {
			si->sem_base = AllocVec(sizeof(struct sem) * nsems, MEMF_ANY|MEMF_CLEAR);
			if (si->sem_base) {
				sa = si->sem_base;
				for (i = 0; i < nsems; i++) {
					sem_setup(&sa[i]);
				}
				si->sem_nsems = nsems;
				id = semcx->nobj++;
				semcx->objv[id] = (struct IPCGeneric *)si;
			} else {
				sem_destroy(si);
				errno = ENOMEM;
			}
		} else {
			errno = ENOMEM;
		}
	} else if (id == -1) {
		errno = ENOENT;
	}

	IPCUnlock(semcx);

	return id;
}

/* Perform semaphore operations */
int semop(int semid, struct sembuf *sops, size_t nsops)
{
	struct semid_ds_local *si;
	int ret = -1;
	int i, n, t;

	if (!sops || nsops == 0) {
		errno = EFAULT;
		return -1;
	}

	IPCLock(__get_semcx());
	si = GetSemById(semid);
	if (si) {
		struct sem *sa = si->sem_base;
		
		/* Check all operations first */
		for (i = 0; i < nsops; i++) {
			n = sops[i].sem_num;
			if (n < 0 || n >= si->sem_nsems) {
				errno = EFBIG;
				break;
			}
			if (sops[i].sem_op < 0) {
				if (sa[n].semval < -sops[i].sem_op) {
					if (sops[i].sem_flg & IPC_NOWAIT) {
						errno = EAGAIN;
					} else {
						/* For now, just fail - real implementation would block */
						errno = EAGAIN;
					}
					break;
				}
			} else if (sops[i].sem_op == 0) {
				if (sa[n].semval > 0) {
					if (sops[i].sem_flg & IPC_NOWAIT) {
						errno = EAGAIN;
					} else {
						/* For now, just fail - real implementation would block */
						errno = EAGAIN;
					}
					break;
				}
			}
		}

		if (i == nsops) {
			/* All operations ok, perform them */
			for (i = 0; i < nsops; i++) {
				n = sops[i].sem_num;
				t = sops[i].sem_op;
				sa[n].semval += t;
				sa[n].sempid = getpid();
			}
			si->sem_otime = time(NULL);
			ret = 0;
		}
	} else {
		errno = EINVAL;
	}

	IPCUnlock(__get_semcx());

	return ret;
}

/* Control semaphore set */
int semctl(int semid, int semnum, int cmd, ...)
{
	int ret = -1;
	struct semid_ds_local *si;
	struct sem *sb;
	int i;
	va_list ap;
	union semun aun;

	va_start(ap, cmd);
	aun = va_arg(ap, union semun);
	va_end(ap);

	IPCLock(__get_semcx());
	si = GetSemById(semid);
	if (si) {
		sb = (struct sem *)si->sem_base;
		switch (cmd) {
		case IPC_STAT:
			if (aun.buf) {
				memcpy(aun.buf, si, sizeof(struct semid_ds_local));
				ret = 0;
			} else {
				errno = EFAULT;
			}
			break;
		case IPC_SET:
			ret = 0;  /* Silently ignore for now */
			break;
		case IPC_RMID:
			IPCRmId(__get_semcx(), semid, (void (*)(struct IPCGeneric *))sem_destroy);
			ret = 0;
			break;
		case GETVAL:
			if (semnum >= 0 && semnum < si->sem_nsems) {
				ret = sb[semnum].semval;
			} else {
				errno = EINVAL;
			}
			break;
		case SETVAL:
			if (semnum >= 0 && semnum < si->sem_nsems) {
				sb[semnum].semval = aun.val;
				ret = 0;
			} else {
				errno = EINVAL;
			}
			break;
		case GETPID:
			if (semnum >= 0 && semnum < si->sem_nsems) {
				ret = sb[semnum].sempid;
			} else {
				errno = EINVAL;
			}
			break;
		case GETNCNT:
			if (semnum >= 0 && semnum < si->sem_nsems) {
				ret = sb[semnum].semncnt;
			} else {
				errno = EINVAL;
			}
			break;
		case GETZCNT:
			if (semnum >= 0 && semnum < si->sem_nsems) {
				ret = sb[semnum].semzcnt;
			} else {
				errno = EINVAL;
			}
			break;
		case SETALL:
			if (aun.array) {
				for (i = 0; i < si->sem_nsems; i++) {
					sb[i].semval = aun.array[i];
				}
				ret = 0;
			} else {
				errno = EFAULT;
			}
			break;
		case GETALL:
			if (aun.array) {
				for (i = 0; i < si->sem_nsems; i++) {
					aun.array[i] = sb[i].semval;
				}
				ret = 0;
			} else {
				errno = EFAULT;
			}
			break;
		default:
			errno = EINVAL;
		}
	} else {
		errno = EINVAL;
	}

	IPCUnlock(__get_semcx());

	return ret;
}
