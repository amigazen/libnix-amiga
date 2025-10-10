/*
 * SystemV IPC common infrastructure for libnix-amiga
 * 
 * This implementation is based on Peter Bengtsson's sysvipc implementation
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <string.h>
#include <exec/exec.h>
#include <dos/dos.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include "ipcprivate.h"

extern struct ExecBase *SysBase;

/* Global IPC key maps for different IPC types */
static struct IPCIdKeyMap semcx = {0};
static struct IPCIdKeyMap shmcx = {0};
static struct IPCIdKeyMap msgcx = {0};

/* Initialize IPC key map */
void IPCMapInit(struct IPCIdKeyMap *m)
{
	m->nobj = 0;
	m->vlen = 16;  /* Start with 16 entries */
	m->idx = 0;
	m->nused = 0;
	m->objv = AllocVec(sizeof(void *) * m->vlen, MEMF_ANY|MEMF_CLEAR);
	m->Lock = AllocMem(sizeof(struct SignalSemaphore), MEMF_ANY|MEMF_CLEAR);
	if (m->Lock) {
		InitSemaphore(m->Lock);
	}
}

/* Cleanup IPC key map */
void IPCMapUninit(struct IPCIdKeyMap *m)
{
	if (m->objv) {
		FreeVec(m->objv);
		m->objv = NULL;
	}
	if (m->Lock) {
		FreeMem(m->Lock, sizeof(struct SignalSemaphore));
		m->Lock = NULL;
	}
}

/* Get IPC object by ID */
void *GetIPCById(struct IPCIdKeyMap *m, int id)
{
	if (id < 0 || id >= m->nobj || !m->objv) {
		return NULL;
	}
	return m->objv[id];
}

/* Lock IPC key map */
void IPCLock(struct IPCIdKeyMap *m)
{
	if (m->Lock) {
		ObtainSemaphore(m->Lock);
	}
}

/* Unlock IPC key map */
void IPCUnlock(struct IPCIdKeyMap *m)
{
	if (m->Lock) {
		ReleaseSemaphore(m->Lock);
	}
}

/* Get IPC key ID (simplified version) */
int GetIPCKeyId(struct IPCIdKeyMap *m, key_t key, int flags, void *(*Construct)(int, int))
{
	int id = -1;
	void *obj;
	
	/* For now, use a simple linear search */
	{
		int i;
		for (i = 0; i < m->nobj; i++) {
		if (m->objv[i]) {
			/* Check if key matches - simplified */
			/* In real implementation, would check key field */
			if (key == IPC_PRIVATE || (flags & IPC_CREAT)) {
				id = i;
				break;
			}
		}
		}
	}
	
	/* If not found and CREATE flag set, create new entry */
	if (id == -1 && (flags & IPC_CREAT)) {
		if (m->nobj < m->vlen) {
			obj = Construct(key, flags);
			if (obj) {
				id = m->nobj++;
				m->objv[id] = obj;
			}
		} else {
			errno = ENOSPC;
		}
	} else if (id == -1) {
		errno = ENOENT;
	}
	
	return id;
}

/* Remove IPC ID */
void IPCRmId(struct IPCIdKeyMap *m, int id, void (*Destroy)(struct IPCGeneric *))
{
	if (id >= 0 && id < m->nobj && m->objv[id]) {
		if (Destroy) {
			Destroy(m->objv[id]);
		}
		m->objv[id] = NULL;
	}
}

/* Initialize all IPC subsystems */
void __ipc_init(void)
{
	IPCMapInit(&semcx);
	IPCMapInit(&shmcx);
	IPCMapInit(&msgcx);
}

/* Cleanup all IPC subsystems */
void __ipc_cleanup(void)
{
	IPCMapUninit(&semcx);
	IPCMapUninit(&shmcx);
	IPCMapUninit(&msgcx);
}

/* Get semaphore context */
struct IPCIdKeyMap *__get_semcx(void)
{
	return &semcx;
}

/* Get shared memory context */
struct IPCIdKeyMap *__get_shmcx(void)
{
	return &shmcx;
}

/* Get message queue context */
struct IPCIdKeyMap *__get_msgcx(void)
{
	return &msgcx;
}

/* Get IPC IDs */
int IPCids(struct IPCIdKeyMap *m, int *idbuf, int idblen, unsigned int *idcnt)
{
	int i, count = 0;
	
	if (!m || !idbuf || !idcnt) {
		errno = EFAULT;
		return -1;
	}
	
	for (i = 0; i < m->nobj && count < idblen; i++) {
		if (m->objv[i]) {
			idbuf[count++] = i;
		}
	}
	
	*idcnt = count;
	return 0;
}
