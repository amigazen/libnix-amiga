/*
 * SystemV IPC private header definitions for libnix-amiga
 * 
 * This implementation is based on Peter Bengtsson's sysvipc implementation
 */

#ifndef	IPC_PRIVATE_H__
#define	IPC_PRIVATE_H__

#include <sys/ipc.h>
#include <exec/exec.h>

struct IPCGeneric {	/* Common header for all ipc structures. */
	struct ipc_perm	perm;
};

struct IPCIdKeyMap {
	int nobj,vlen,idx,nused;	/* Highest valid index + 1, vector length, total created objects, total used slots */
	struct IPCGeneric **objv;
	struct SignalSemaphore *Lock;
};

extern int GetIPCKeyId(struct IPCIdKeyMap *m,key_t key,int flags,void *(*Construct)(int,int));
extern void IPCMapUninit(struct IPCIdKeyMap *m);
extern void IPCMapInit(struct IPCIdKeyMap *m);
extern void *GetIPCById(struct IPCIdKeyMap *m,int id);
extern void IPCLock(struct IPCIdKeyMap *m);
extern void IPCUnlock(struct IPCIdKeyMap *m);
extern void *GetIPCByP(struct IPCIdKeyMap *m,int (*eq)(void *,void *),void *v,int *id);
extern void IPCRmId(struct IPCIdKeyMap *m,int id,void (*Destroy)(struct IPCGeneric *));
extern int IPCids(struct IPCIdKeyMap *m,int *idbuf,int idblen,unsigned int *idcnt);

#endif
