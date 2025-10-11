/*
 * SystemV IPC semaphore header definitions for libnix-amiga
 * 
 * This implementation is based on Peter Bengtsson's sysvipc implementation
 */

#ifndef _SYS_SEM_H_
#define	_SYS_SEM_H_

#include <sys/ipc.h>
#include <sys/types.h>

/* Semaphores */

#define	SEM_R		0400
#define	SEM_W		0200

/* Semaphore control commands */
#define	GETVAL		0	/* Get semaphore value */
#define	SETVAL		16	/* Set semaphore value */
#define	GETPID		17	/* Get semaphore PID */
#define	GETNCNT		18	/* Get number of processes waiting for semval > curval */
#define	GETZCNT		19	/* Get number of processes waiting for semval == 0 */
#define	SETALL		20	/* Set all semaphore values */
#define	GETALL		21	/* Get all semaphore values */

#define	SEM_UNDO	020000

/* Union for semctl */
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

struct sembuf {
	unsigned short sem_num;
	short sem_op;
	short sem_flg;
};

struct sem {
	int	semval;
	pid_t	sempid;
	unsigned short	semncnt;
	unsigned short	semzcnt;
};

struct semid_ds {
	struct ipc_perm sem_perm;
	struct sem *sem_base;
	int		nsem_nsems;
	time_t	sem_otime;
	time_t	sem_ctime;
	int		sem_binary;
};

/* Function prototypes */
int semget(key_t key, int nsems, int semflg);
int semop(int semid, struct sembuf *sops, size_t nsops);
int semctl(int semid, int semnum, int cmd, ...);

#endif /* _SYS_SEM_H_ */