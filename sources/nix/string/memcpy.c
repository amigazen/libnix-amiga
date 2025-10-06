#include <string.h>
#include <proto/exec.h>

void *memcpy(void *s1,const void *s2,size_t n)
{
  CopyMem((APTR)s2,(APTR)s1,n);
  return s1;
}
