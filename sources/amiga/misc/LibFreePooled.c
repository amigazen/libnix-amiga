#include <pool.h>

VOID LibFreePooled(APTR poolHeader, APTR memory, ULONG memSize)
{
  AsmFreePooled(poolHeader,memory,memSize,*(struct ExecBase **)4L);
}
