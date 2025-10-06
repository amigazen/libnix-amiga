#include <exec/lists.h>
#include <clib/alib_protos.h>

void NewList(struct List *list)
{
   LONG *p;

   list->lh_TailPred=(struct Node*)list;
   ((LONG *)list)++;
   *(LONG *)list=0;
   p=(LONG *)list; *--p=(LONG)list;
}
