/*
 * SystemV IPC message queue functions for libnix-amiga
 * 
 * This implementation is based on Peter Bengtsson's sysvipc implementation
 */

#include <sys/msg.h>
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
extern struct IPCIdKeyMap *__get_msgcx(void);

#define	DEFAULT_QSIZE	4096

/* Message structure */
struct Msg {
	struct Msg *Next;
	unsigned long Size;
	long Type;
	unsigned char Data[1];
};

/* Internal message queue structure with additional fields */
struct msgqid_ds_internal {
	struct IPCGeneric	generic;	/* Must be first for IPCGeneric compatibility */
	struct Msg	*msg_first;	/* Pointer to first message on queue */
	struct Msg	*msg_last;	/* Pointer to last message on queue */
	msglen_t	msg_cbytes;	/* Current number of bytes on queue */
	msgqnum_t	msg_qnum;	/* Current number of messages on queue */
	msglen_t	msg_qbytes;	/* Maximum number of bytes on queue */
	pid_t		msg_lspid;	/* PID of last msgsnd */
	pid_t		msg_lrpid;	/* PID of last msgrcv */
	time_t		msg_stime;	/* Last msgsnd time */
	time_t		msg_rtime;	/* Last msgrcv time */
	time_t		msg_ctime;	/* Last change time */
};

/* Construct message queue */
static struct msgqid_ds_internal *msg_construct(int key, int flags)
{
	struct msgqid_ds_internal *qi;
	
	qi = AllocVec(sizeof(struct msgqid_ds_internal), MEMF_ANY|MEMF_CLEAR);
	if (qi) {
		qi->generic.perm.mode = flags & 0777;
		qi->generic.perm.key = key;
		qi->msg_first = NULL;
		qi->msg_last = NULL;
		qi->msg_cbytes = 0;
		qi->msg_qnum = 0;
		qi->msg_qbytes = DEFAULT_QSIZE;
		qi->msg_ctime = time(NULL);
	}
	return qi;
}

/* Destroy message queue */
static void msg_destroy(struct msgqid_ds_internal *qi)
{
	struct Msg *m, *rm;
	
	if (qi) {
		m = qi->msg_first;
		while (m) {
			rm = m;
			m = m->Next;
			FreeVec(rm);
		}
		FreeVec(qi);
	}
}

/* Get message queue by ID */
static struct msgqid_ds_internal *GetMsgById(int id)
{
	return (struct msgqid_ds_internal *)GetIPCById(__get_msgcx(), id);
}

/* Create or get message queue */
int msgget(key_t key, int msgflg)
{
	int id = -1;
	struct msgqid_ds_internal *qi;
	struct IPCIdKeyMap *msgcx = __get_msgcx();

	IPCLock(msgcx);

	/* Simple implementation - always create new if not found */
	{
		int i;
		for (i = 0; i < msgcx->nobj; i++) {
		if (msgcx->objv[i]) {
			qi = (struct msgqid_ds_internal *)msgcx->objv[i];
			if (qi->generic.perm.key == key) {
				if (msgflg & IPC_CREAT && msgflg & IPC_EXCL) {
					errno = EEXIST;
					break;
				}
				id = i;
				break;
			}
		}
		}
	}

	if (id == -1 && (msgflg & IPC_CREAT)) {
		/* Create new message queue */
		qi = msg_construct(key, msgflg);
		if (qi) {
			id = msgcx->nobj++;
			msgcx->objv[id] = (struct IPCGeneric *)qi;
		} else {
			errno = ENOMEM;
		}
	} else if (id == -1) {
		errno = ENOENT;
	}

	IPCUnlock(msgcx);

	return id;
}

/* Send message to queue */
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg)
{
	struct msgqid_ds_internal *qi;
	int ret = -1;
	struct Msg *m;
	struct IPCIdKeyMap *msgcx = __get_msgcx();

	if (!msgp) {
		errno = EFAULT;
		return -1;
	}

	IPCLock(msgcx);
	qi = GetMsgById(msqid);
	if (qi) {
		/* Check if message fits in queue */
		if (msgsz > qi->msg_qbytes) {
			if (msgflg & MSG_NOERROR) {
				ret = 0;  /* Silently truncate */
			} else {
				errno = EINVAL;
			}
		} else if (qi->msg_cbytes + msgsz > qi->msg_qbytes) {
			if (msgflg & IPC_NOWAIT) {
				errno = EAGAIN;
			} else {
				/* For now, just fail - real implementation would block */
				errno = EAGAIN;
			}
		} else {
			/* Allocate and add message */
			m = AllocVec(msgsz + sizeof(struct Msg), MEMF_ANY|MEMF_CLEAR);
			if (m) {
				m->Next = NULL;
				m->Size = msgsz;
				memcpy(&m->Type, msgp, msgsz + sizeof(long));
				
				/* Add to queue */
				if (qi->msg_last) {
					qi->msg_last->Next = m;
				} else {
					qi->msg_first = m;
				}
				qi->msg_last = m;
				
				/* Update counters */
				qi->msg_qnum++;
				qi->msg_cbytes += msgsz;
				qi->msg_lspid = getpid();
				qi->msg_stime = time(NULL);
				
				ret = 0;
			} else {
				errno = ENOMEM;
			}
		}
	} else {
		errno = EINVAL;
	}
	IPCUnlock(msgcx);

	return ret;
}

/* Receive message from queue */
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg)
{
	struct msgqid_ds_internal *qi;
	ssize_t ret = -1;
	struct Msg *m, *prev;
	int nbytes;
	struct IPCIdKeyMap *msgcx = __get_msgcx();

	if (!msgp) {
		errno = EFAULT;
		return -1;
	}

	IPCLock(msgcx);
	qi = GetMsgById(msqid);
	if (qi) {
		prev = NULL;
		m = qi->msg_first;
		
		/* Find message by type */
		if (msgtyp > 0) {
			while (m) {
				if (m->Type == msgtyp) {
					break;
				}
				prev = m;
				m = m->Next;
			}
		} else if (msgtyp < 0) {
			msgtyp = -msgtyp;
			while (m) {
				if (m->Type <= msgtyp) {
					break;
				}
				prev = m;
				m = m->Next;
			}
		}
		
		if (m) {
			/* Remove message from queue */
			if (prev) {
				prev->Next = m->Next;
			} else {
				qi->msg_first = m->Next;
			}
			if (qi->msg_last == m) {
				qi->msg_last = prev;
			}
			
			nbytes = sizeof(long) + ((m->Size <= msgsz) ? m->Size : msgsz);
			if ((m->Size <= msgsz) || (msgflg & IPC_NOERROR)) {
				memcpy(msgp, &m->Type, nbytes);
				qi->msg_cbytes -= m->Size;
				qi->msg_qnum--;
				qi->msg_lrpid = getpid();
				qi->msg_rtime = time(NULL);
				FreeVec(m);
				ret = nbytes;
			} else {
				errno = E2BIG;
			}
		} else if (msgflg & IPC_NOWAIT) {
			errno = ENOMSG;
		} else {
			/* For now, just fail - real implementation would block */
			errno = ENOMSG;
		}
	} else {
		errno = EINVAL;
	}
	IPCUnlock(msgcx);

	return ret;
}

/* Control message queue */
int msgctl(int msqid, int cmd, struct msgqid_ds *buf)
{
	struct msgqid_ds_internal *qi;
	int ret = -1;
	struct IPCIdKeyMap *msgcx = __get_msgcx();

	IPCLock(msgcx);
	qi = GetMsgById(msqid);
	if (qi) {
		switch (cmd) {
		case IPC_STAT:
			if (buf) {
				/* Copy internal structure to public structure */
				buf->msg_perm = qi->generic.perm;
				buf->msg_first = qi->msg_first;
				buf->msg_last = qi->msg_last;
				buf->msg_cbytes = qi->msg_cbytes;
				buf->msg_qnum = qi->msg_qnum;
				buf->msg_qbytes = qi->msg_qbytes;
				buf->msg_lspid = qi->msg_lspid;
				buf->msg_lrpid = qi->msg_lrpid;
				buf->msg_stime = qi->msg_stime;
				buf->msg_rtime = qi->msg_rtime;
				buf->msg_ctime = qi->msg_ctime;
				ret = 0;
			} else {
				errno = EFAULT;
			}
			break;
		case IPC_SET:
			if (buf && buf->msg_qbytes > 0) {
				qi->msg_qbytes = buf->msg_qbytes;
				ret = 0;
			} else {
				errno = EINVAL;
			}
			break;
		case IPC_RMID:
			IPCRmId(msgcx, msqid, (void (*)(struct IPCGeneric *))msg_destroy);
			ret = 0;
			break;
		default:
			errno = EINVAL;
		}
	} else {
		errno = EINVAL;
	}
	IPCUnlock(msgcx);

	return ret;
}