#include <exec/lists.h>
#include <exec/memory.h>
#include <exec/execbase.h>
#include <clib/alib_protos.h>
#include <proto/exec.h>

/*     our PRIVATE! memory pool structure 
   (_NOT_ compatible with original amiga.lib!) */

typedef struct Pool
{
  struct MinList PuddleList;
  struct MinList ThreshList;
  ULONG MemoryFlags;
  ULONG PuddleSize;
  ULONG ThreshSize;
} POOL;
