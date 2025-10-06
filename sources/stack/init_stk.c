#include <proto/exec.h>
#include <proto/dos.h>
#include <stabs.h>

extern APTR __SaveSP;
extern ULONG __stk_safezone;

APTR  __stk_limit=NULL;
APTR *__stackborders=NULL;

/*
 * This way to find the bottom of the current stackframe
 * is the way descibed in the amiga-guru-book.
 *
 * Note that it's of no use to check if the actual parameters are set
 * correctly (disabling stackextension if not) because a program will
 * crash anyway in that case (if you check against the wrong border or
 * not at all).
 * But with wrong parameters you can probably raise a stackextend too
 * soon - thus gaining *correct* (for following stackextends) stackbounds
 * at the cost of only some memory.
 */

void __init_stk(void)
{
  struct Process *me;
  APTR sl;

  me=(struct Process *)FindTask(NULL);
  __stackborders=&me->pr_Task.tc_SPLower;
  sl=&me->pr_Task.tc_SPLower;
  if(me->pr_CLI)
    sl=(char *)me->pr_ReturnAddr /*+sizeof(ULONG)*/ -*(ULONG *)me->pr_ReturnAddr;
  			         /*^^^^^^^^^^^^^^ need not be that precise */
  sl+=__stk_safezone;
  __stk_limit=sl;
}

ADD2INIT(__init_stk,-50);
