/*
 * SystemV IPC shared memory header definitions for libnix-amiga
 * 
 * This implementation is based on Peter Bengtsson's sysvipc implementation
 */

#ifndef _SYS_SHM_H_
#define	_SYS_SHM_H_

#include <sys/ipc.h>
#include <sys/types.h>

/* Shared memory flags */
#define	SHM_R		0400
#define	SHM_W		0200

#define	SHMLBA		0x10000	/* Replace with a call to determine pagesize? */
#define	SHM_RDONLY	(1L<<0)
#define	SHM_RND		(1L<<0)

#define	SHM_LOCK		11
#define	SHM_UNLOCK	12

/* Shared memory segment data structure */
struct shmid_ds {
	struct ipc_perm	shm_perm;
	size_t		shm_segsz;
	pid_t		shm_lpid;	/* PID of last shmop */
	pid_t		shm_cpid;	/* PID of creator */
	int		shm_nattach;	/* Number of current attaches */
	time_t		shm_atime;	/* Last attach time */
	time_t		shm_dtime;	/* Last detach time */
	time_t		shm_ctime;	/* Last change time */
};

/* Function prototypes */
void *shmat(int shmid, const void *prefadds, int flags);
int shmdt(void *shmaddr);
int shmget(key_t key, size_t size, int flags);
int shmctl(int shmid, int cmd, struct shmid_ds *cbuf);

#endif /* _SYS_SHM_H_ */
