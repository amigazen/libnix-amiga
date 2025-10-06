#include <pool.h>

APTR LibAllocPooled(APTR poolHeader, ULONG memSize)
{
  return AsmAllocPooled(poolHeader,memSize,*(struct ExecBase **)4L);
}
