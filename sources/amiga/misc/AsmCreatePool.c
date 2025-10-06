#include <pool.h>

#define NEWLIST(l) ((l)->mlh_Head = (struct MinNode *)&(l)->mlh_Tail, \
                    (l)->mlh_Tail = NULL, \
                    (l)->mlh_TailPred = (struct MinNode *)&(l)->mlh_Head)

APTR AsmCreatePool(ULONG requirements REG(d0), ULONG puddleSize REG(d1), ULONG threshSize REG(d2), struct ExecBase *SysBase REG(a6))
{
  if (SysBase->LibNode.lib_Version>=39)
    return (CreatePool(requirements,puddleSize,threshSize));
  else {

    POOL *pool=NULL;

    if (threshSize<=puddleSize) {
      puddleSize+=7;
      if ((pool=(POOL *)AllocMem(sizeof(POOL),MEMF_ANY))!=NULL) {
        NEWLIST(&pool->PuddleList);
        pool->MemoryFlags=requirements;
        pool->PuddleSize=puddleSize&~7;
        pool->ThreshSize=threshSize;
      }
    }
    return pool;
  }
}

VOID AsmDeletePool(POOL *poolHeader REG(a0), struct ExecBase *SysBase REG(a6))
{
  if (SysBase->LibNode.lib_Version>=39)
    DeletePool(poolHeader);
  else {

    if (poolHeader!=NULL) {

      ULONG *pool,size;

      while((pool=(ULONG *)RemHead((struct List *)&poolHeader->PuddleList))!=NULL) {
        size=*--pool; FreeMem(pool,size);
      }
      FreeMem(poolHeader,sizeof(POOL));
    }
  }
}
