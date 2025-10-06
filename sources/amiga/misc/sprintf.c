#include <proto/exec.h>
#include <stdarg.h>

static const ULONG tricky=0x16c04e75; /* move.b d0,(a3)+ ; rts */

void sprintf(STRPTR buffer,STRPTR fmt,...)
{ RawDoFmt(fmt,(ULONG *)&fmt+1,(void (*)())&tricky,buffer); } /* Not very clean, but ... */
