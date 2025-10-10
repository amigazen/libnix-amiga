/*
 * SystemV IPC message queue header definitions for libnix-amiga
 * 
 * This implementation is based on Peter Bengtsson's sysvipc implementation
 */

#ifndef _SYS_MSG_H_
#define	_SYS_MSG_H_

#include <sys/ipc.h>
#include <sys/types.h>

/* Message Queue Error Codes */
#ifndef ENOMSG
#define ENOMSG 83		/* No message of desired type */
#endif

/* Message Queues */

#define	MSG_R		0400
#define	MSG_W		0200

typedef	unsigned int	msglen_t;
typedef	unsigned int	msgqnum_t;

struct msgsnap_head {
	size_t	msgsnap_size;
	size_t	msgsnap_nmsg;
};

struct msgsnap_mhead {
	size_t	msgsnap_mlen;
	long int	msgsnap_mtype;
};

struct msgqid_ds {
	struct ipc_perm	msg_perm;
	void		*msg_first;
	void		*msg_last;
	msglen_t	msg_cbytes;
	msgqnum_t	msg_qnum;
	msglen_t	msg_qbytes;
	pid_t		msg_lspid;
	pid_t		msg_lrpid;
	time_t		msg_stime;
	time_t		msg_rtime;
	time_t		msg_ctime;
	void		*Lock;
	void		*WList,*RList;
};

/* Function prototypes */
int msgget(key_t key, int flags);
int msgsnd(int qid, const void *msg, size_t mlen, int flags);
ssize_t msgrcv(int qid, void *msg, size_t mlen, long int mtype, int flags);
int msgctl(int qid, int cmd, struct msgqid_ds *buf);
int msgsnap(int qid, void *qbuf, size_t blen, long mtype);
int msgids(int *buf, unsigned int blen, unsigned int *qcnt);

#endif /* _SYS_MSG_H_ */
