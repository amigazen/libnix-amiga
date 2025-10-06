#include <proto/exec.h>
#include <stabs.h>

extern void __openliberror(ULONG, char*) __attribute__ ((noreturn));

extern struct lib /* These are the elements pointed to by __LIB_LIST__ */
{ struct Library *base;
  char *name;
} *__LIB_LIST__[];

extern ULONG __oslibversion;

void __initlibraries(void)
{
  ULONG version=__oslibversion;
  struct lib **list=__LIB_LIST__;
  ULONG numbases=(ULONG)*list++;

  if(numbases)
    do {
      struct lib *l=*list++;
      if((l->base=OpenLibrary(l->name,version))==NULL)
        __openliberror(version,l->name);
    } while(--numbases);
}

void __exitlibraries(void)
{
  struct lib **list=__LIB_LIST__;
  ULONG numbases=(ULONG)*list++;

  if(numbases)
    do {
      struct lib *l=*list++;
      struct Library *lb=l->base;
      if(lb!=NULL) {
        /* l->base=NULL; */
        CloseLibrary(lb);
      }
    } while(--numbases);
}

ADD2INIT(__initlibraries,-60);
ADD2EXIT(__exitlibraries,-60);
