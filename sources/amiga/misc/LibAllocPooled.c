#include <pool.h>

APTR LibAllocPooled(APTR poolHeader, ULONG memSize)
{
  if (SysBase->LibNode.lib_Version>=39)
    return (AllocPooled(poolHeader,memSize));
  else
  {
    POOL *pool=(POOL *)poolHeader;
    ULONG *puddle=NULL;

    if (memSize!=0 && poolHeader!=NULL)
    {
      if (pool->ThreshSize>memSize)
      {
        struct MinNode *node=pool->PuddleList.mlh_Head;

        for(;;)
         {
           struct MemHeader *a;
           ULONG size;

           if ((ULONG *)node->mln_Succ!=puddle /* NULL! */)
           {
             if ((puddle=(ULONG *)Allocate((struct MemHeader *)node,memSize))!=NULL)
               break;
             node=node->mln_Succ; continue;
           }
           size=pool->PuddleSize+sizeof(struct MemHeader)+2*sizeof(ULONG);
           if ((puddle=(ULONG *)AllocMem(size,pool->MemoryFlags))==NULL)
             goto out; /* why is gcc so dumb ??? */

           *puddle++=size;
           a=(struct MemHeader *)puddle;
           a->mh_Lower=a->mh_First=(struct MemChunk *)((UBYTE *)a+sizeof(struct MemHeader)+sizeof(UBYTE *));
           a->mh_First->mc_Next=NULL;
           a->mh_Free=a->mh_First->mc_Bytes=pool->PuddleSize;
           a->mh_Upper=(char *)a->mh_First+a->mh_Free;
           AddHead((struct List *)&pool->PuddleList,&a->mh_Node);
           puddle=(ULONG *)Allocate(a,memSize);
           break;
         }

        if (pool->MemoryFlags&MEMF_CLEAR)
        {
          ULONG *p=puddle;

          memSize=(memSize+7)>>3;
          do { *p++=0; *p++=0; } while(--memSize);
        }
      }
      else
      {
        ULONG size=memSize+sizeof(struct MinNode)+sizeof(ULONG);

        if ((puddle=(ULONG *)AllocMem(size,pool->MemoryFlags))!=NULL)
        {
          *puddle++=size;
          AddHead((struct List *)&pool->ThreshList,(struct Node *)puddle);
          puddle=(ULONG *)((struct MinNode *)puddle+1);
        }
      }
    }
out:
    return puddle;
  }
}
