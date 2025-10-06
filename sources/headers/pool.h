#include <exec/types.h>

#if !defined(__GNUC__)
#define REG(x)
#else
#define REG(x) __asm(#x)
#endif

#include <exec/lists.h>
#include <exec/memory.h>
#include <exec/execbase.h>
#include <proto/exec.h>

/*
**     our PRIVATE! memory pool structure 
** (_NOT_ compatible with original amiga.lib!)
*/

typedef struct Pool {
  struct MinList PuddleList;
  ULONG MemoryFlags;
  ULONG PuddleSize;
  ULONG ThreshSize;
} POOL;

/*
** required prototypes ;)
*/

APTR AsmCreatePool(ULONG REG(d0),ULONG REG(d1),ULONG REG(d2),struct ExecBase * REG(a6));
APTR AsmAllocPooled(POOL * REG(a0),ULONG REG(d0),struct ExecBase * REG(a6));
VOID AsmFreePooled(POOL * REG(a0),APTR REG(a1),ULONG REG(d0), struct ExecBase * REG(a6));
VOID AsmDeletePool(POOL * REG(a0),struct ExecBase * REG(a6));
