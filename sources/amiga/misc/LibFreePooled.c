#include <pool.h>

VOID LibFreePooled(APTR poolHeader, APTR memory, ULONG memSize)
{
  if (SysBase->LibNode.lib_Version>=39)
    return (FreePooled(poolHeader,memory,memSize));
  else
  {
    if (poolHeader!=NULL && memory!=NULL)
    {
      POOL *pool=(POOL *)poolHeader;
      ULONG *puddle,size;

      if (pool->ThreshSize>memSize)
      {
        struct MemHeader *a=(struct MemHeader *)pool->PuddleList.mlh_Head;

        for(;;)
         {
           if (a->mh_Node.ln_Succ==NULL)
             return;
           if (memory>=a->mh_Lower && memory<a->mh_Upper)
             break;
           a=(struct MemHeader *)a->mh_Node.ln_Succ;
         }
        Deallocate(a,memory,memSize);
        if (a->mh_Free!=pool->PuddleSize)
          return;
        puddle=(ULONG *)&a->mh_Node;
      }
      else
        puddle=(ULONG *)((struct MinNode *)memory-1);
      Remove((struct Node *)puddle);
      size=*(--((ULONG *)puddle));
      FreeMem(puddle,size);
    }
  }
}
