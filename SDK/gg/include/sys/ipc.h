/*
 * SystemV IPC header definitions for libnix-amiga
 * 
 * This implementation is based on Peter Bengtsson's sysvipc implementation
 */

#ifndef _SYS_IPC_H_
#define	_SYS_IPC_H_

#include <sys/types.h>

/* key_t is already defined in sys/types.h */

/* Permission structure for IPC objects */
struct ipc_perm {
	uid_t	uid;		/* Owner's UID.  Matches UID/GID types in dos/dos.h */
	gid_t	gid;		/* Owner's GID */
	uid_t	cuid;		/* Creator's UID */
	gid_t	cgid;		/* Creator's GID */
	mode_t	mode;		/* Protection flags. */
	unsigned int	seq;	/* Sequence no. */
	key_t	key;		/* IPC key */
};

/* IPC operation flags */
#define	IPC_CREAT	001000
#define	IPC_EXCL	002000
#define	IPC_NOWAIT	004000
#define	IPC_NOERROR	010000
#define	MSG_NOERROR	IPC_NOERROR	/* Alias for IPC_NOERROR */

/* Modeflags for extra things */
#define	SHM_CLEAR		001000	/* shm segment has never been attached - NOTE: same value as IPC_CREAT */
#define	IPC_DELETE		002000	/* resource is scheduled to be deleted */
#define	MSG_SENDWAIT	004000	/* message queue is full (waiting on send) */
#define	MSG_RECVWAIT	010000	/* message queue is empty (waiting on recv) */

/* IPC control commands */
#define	IPC_RMID	1
#define	IPC_SET	2
#define	IPC_STAT	3

/* Common IPC limits */
#define	IPC_PRIVATE	((key_t)0x80000000L)

/* Function prototypes */
key_t ftok(const char *path, int id);

#endif /* _SYS_IPC_H_ */
