/*
 * SystemV IPC key generation function for libnix-amiga
 * 
 * This implementation is based on Peter Bengtsson's sysvipc implementation
 */

#include <sys/ipc.h>
#include <errno.h>
#include <string.h>
#include <exec/exec.h>
#include <dos/dos.h>
#include <proto/exec.h>
#include <proto/dos.h>

extern struct ExecBase *SysBase;

/*
 * Generate a System V IPC key from a pathname and project ID.
 */
key_t ftok(const char *path, int id)
{
	key_t key = (key_t)-1;
	BPTR lock = 0;
	ULONG blockno = 0;
	struct FileLock *flock;
	struct Library *DOSBase;

	if (!path) {
		errno = EFAULT;
		return (key_t)-1;
	}

	DOSBase = OpenLibrary("dos.library", 0);
	if (!DOSBase) {
		errno = ENOENT;
		return (key_t)-1;
	}

	lock = Lock((STRPTR)path, SHARED_LOCK);
	if (lock) {
		flock = BADDR(lock);
		blockno = flock->fl_Key;
		UnLock(lock);
		key = (blockno << 8) | (id & 0xFF);
	} else {
		errno = ENOENT;
	}

	CloseLibrary(DOSBase);

	return key;
}
