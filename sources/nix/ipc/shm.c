/*
 * SystemV IPC shared memory functions for libnix-amiga
 * 
 * This implementation is based on Peter Bengtsson's sysvipc implementation
 */

#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>
#include <string.h>
#include <exec/exec.h>
#include <dos/dos.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <proto/exec.h>
#include "ipcprivate.h"

extern struct ExecBase *SysBase;

/* Forward declarations for IPC functions */
extern struct IPCIdKeyMap *__get_shmcx(void);

/* Additional fields for internal use */
#define	SHMFLG_DeleteMe	(1L<<0)

/* Internal structure with additional fields */
struct shm_internal {
	struct shmid_ds	shm_ds;
	void		*shm_amp;
	int		flags;
};

/* Construct shared memory segment */
static struct shm_internal *shm_construct(int key, int flags)
{
	struct shm_internal *si;
	
	si = AllocVec(sizeof(struct shm_internal), MEMF_ANY|MEMF_CLEAR);
	if (si) {
		si->shm_amp = NULL;
		si->shm_ds.shm_perm.mode = (flags & 0777);
		si->shm_ds.shm_perm.key = key;
		si->shm_ds.shm_segsz = 0;
		si->shm_ds.shm_ctime = time(NULL);
		si->flags = 0;
	}
	return si;
}

/* Destroy shared memory segment */
static void shm_destroy(struct shm_internal *si)
{
	if (si) {
		if (si->shm_amp) {
			FreeVec(si->shm_amp);
		}
		FreeVec(si);
	}
}

/* Get shared memory segment by ID */
static struct shm_internal *GetShmById(int id)
{
	return (struct shm_internal *)GetIPCById(__get_shmcx(), id);
}

/* Find shared memory segment by address */
static int find_shm_by_addr(void *addr)
{
	struct IPCIdKeyMap *shmcx = __get_shmcx();
	struct shm_internal *si;
	int i;
	
	for (i = 0; i < shmcx->nobj; i++) {
		if (shmcx->objv[i]) {
			si = (struct shm_internal *)shmcx->objv[i];
			if (si->shm_amp == addr) {
				return i;
			}
		}
	}
	return -1;
}

/* Create or get shared memory segment */
int shmget(key_t key, size_t size, int shmflg)
{
	int id = -1;
	struct shm_internal *si;
	struct IPCIdKeyMap *shmcx = __get_shmcx();

	if (size == 0) {
		errno = EINVAL;
		return -1;
	}

	IPCLock(shmcx);

	/* Simple implementation - always create new if not found */
	{
		int i;
		for (i = 0; i < shmcx->nobj; i++) {
		if (shmcx->objv[i]) {
			si = (struct shm_internal *)shmcx->objv[i];
			if (si->shm_ds.shm_perm.key == key) {
				if (shmflg & IPC_CREAT && shmflg & IPC_EXCL) {
					errno = EEXIST;
					break;
				}
				id = i;
				break;
			}
		}
		}
	}

	if (id == -1 && (shmflg & IPC_CREAT)) {
		/* Create new shared memory segment */
		si = shm_construct(key, shmflg);
		if (si) {
			si->shm_amp = AllocVec(size, MEMF_ANY|MEMF_CLEAR);
			if (si->shm_amp) {
				si->shm_ds.shm_segsz = size;
				si->shm_ds.shm_cpid = getpid();
				id = shmcx->nobj++;
				shmcx->objv[id] = (struct IPCGeneric *)si;
			} else {
				shm_destroy(si);
				errno = ENOMEM;
			}
		} else {
			errno = ENOMEM;
		}
	} else if (id == -1) {
		errno = ENOENT;
	}

	IPCUnlock(shmcx);

	return id;
}

/* Attach shared memory segment */
void *shmat(int shmid, const void *shmaddr, int shmflg)
{
	void *addr = (void *)-1;
	struct shm_internal *si;
	struct IPCIdKeyMap *shmcx = __get_shmcx();

	IPCLock(shmcx);
	si = GetShmById(shmid);
	if (si) {
		if (shmaddr == NULL || shmaddr == si->shm_amp) {
			si->shm_ds.shm_nattach++;
			addr = si->shm_amp;
			si->shm_ds.shm_atime = time(NULL);
			si->shm_ds.shm_lpid = getpid();
		} else {
			errno = EINVAL;
		}
	} else {
		errno = EINVAL;
	}
	IPCUnlock(shmcx);

	return addr;
}

/* Detach shared memory segment */
int shmdt(void *shmaddr)
{
	int id;
	int ret = -1;
	struct shm_internal *si;
	struct IPCIdKeyMap *shmcx = __get_shmcx();

	IPCLock(shmcx);
	id = find_shm_by_addr((void *)shmaddr);
	if (id >= 0) {
		si = (struct shm_internal *)shmcx->objv[id];
		si->shm_ds.shm_nattach--;
		si->shm_ds.shm_dtime = time(NULL);
		si->shm_ds.shm_lpid = getpid();
		
		if (si->shm_ds.shm_nattach == 0 && (si->flags & SHMFLG_DeleteMe)) {
			IPCRmId(shmcx, id, (void (*)(struct IPCGeneric *))shm_destroy);
		}
		ret = 0;
	} else {
		errno = EINVAL;
	}
	IPCUnlock(shmcx);

	return ret;
}

/* Control shared memory segment */
int shmctl(int shmid, int cmd, struct shmid_ds *buf)
{
	int ret = -1;
	struct shm_internal *si;
	struct IPCIdKeyMap *shmcx = __get_shmcx();

	IPCLock(shmcx);
	si = GetShmById(shmid);
	if (si) {
		switch (cmd) {
		case IPC_STAT:
			if (buf) {
				memcpy(buf, &si->shm_ds, sizeof(struct shmid_ds));
				ret = 0;
			} else {
				errno = EFAULT;
			}
			break;
		case IPC_SET:
			ret = 0;
			break;
		case IPC_RMID:
			si->flags |= SHMFLG_DeleteMe;
			si->shm_ds.shm_perm.mode |= IPC_DELETE;
			if (si->shm_ds.shm_nattach == 0) {
				IPCRmId(shmcx, shmid, (void (*)(struct IPCGeneric *))shm_destroy);
			}
			ret = 0;
			break;
		default:
			errno = EINVAL;
		}
	} else {
		errno = EINVAL;
	}
	IPCUnlock(shmcx);

	return ret;
}