#include <pool.h>

extern inline void NewList(struct List *list)
{
   LONG *p;

   list->lh_TailPred=(struct Node*)list;
   ((LONG *)list)++;
   *(LONG *)list=0;
   p=(LONG *)list; *--p=(LONG)list;
}

APTR LibCreatePool(ULONG requirements, ULONG puddleSize, ULONG threshSize)
{
  if (SysBase->LibNode.lib_Version>=39)
    return (CreatePool(requirements,puddleSize,threshSize));
  else
  {
    POOL *pool=NULL;

    if (puddleSize>threshSize)
    { /* make a multiple of 8 */
      puddleSize=(puddleSize+7)&~7;
      /* alloc pool header */
      if ((pool=(POOL *)AllocMem(sizeof(POOL),MEMF_ANY))!=NULL)
      {
        NewList((struct List *)&pool->PuddleList);
        NewList((struct List *)&pool->ThreshList);
        pool->MemoryFlags=requirements;
        pool->PuddleSize=puddleSize;
        pool->ThreshSize=threshSize;
      }
    }
    return pool;
  }
}

VOID LibDeletePool(APTR poolHeader)
{
  if (SysBase->LibNode.lib_Version>=39)
    DeletePool(poolHeader);
  else
    if (poolHeader!=NULL)
    {
      ULONG *pool,size,i;
      struct List *list;

      for(i=2,list=(struct List *)&((POOL *)poolHeader)->PuddleList;i;++list,--i)
       {
         while((pool=(ULONG *)RemHead(list))!=NULL)
         {
           size=*(--((ULONG *)pool)); FreeMem(pool,size);
         }
       }
      FreeMem(poolHeader,sizeof(POOL));
    }
}
