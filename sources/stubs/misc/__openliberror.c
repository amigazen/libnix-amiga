#include <proto/exec.h>

extern void __request(const char *text);
extern void exit(int returncode);

#define NEEDTEXT "Need version %.10ld of %.32s"

const ULONG tricky=0x16c04e75; /* move.b d0,(a3)+ ; rts */

void
__openliberror(ULONG version, char *name)
{ char buf[60];

  RawDoFmt(NEEDTEXT,(APTR)&version,(void (*)())&tricky,buf);
  __request(buf);
  exit(20);
}
