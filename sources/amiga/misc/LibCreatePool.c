#include <pool.h>

APTR LibCreatePool(ULONG requirements, ULONG puddleSize, ULONG threshSize)
{
  return AsmCreatePool(requirements,puddleSize,threshSize,*(struct ExecBase **)4L);
}

VOID LibDeletePool(APTR poolHeader)
{
  AsmDeletePool(poolHeader,*(struct ExecBase **)4L);
}
