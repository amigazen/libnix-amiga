#include <bases.h>
#include <stabs.h>

static const char needtext[]="Need version %.10ld of %.32s";

#ifdef mc68000

asm("
		.text
		.even
Lwriteone:
		moveb	d0,a3@+
		rts

		.even
		.globl	___initlibraries
___initlibraries:
		moveml	d2/d3/a2/a3/a6,sp@-
		movel	"A4(_SysBase)",a6
		movel	"A4(___oslibversion)",d3
		lea	"A4(___LIB_LIST__)",a2
		movel	a2@+,d2
		beq	L3
L5:		movel	a2@+,a3
		movel	a3@(4:W),a1
		movel	d3,d0
		jsr	a6@(-552:W)		| OpenLibrary()
		movel	d0,a3@
		bne	L4
		lea	_needtext,a0
		movel	a3@(4:W),sp@-
		movel	d3,sp@-
		movel	sp,a1
		lea	Lwriteone,a2
		addaw	#-60,sp
		movel	sp,a3
		jsr	a6@(-522:W)		| RawDoFmt()
		movel	a3,sp@-
		jbsr	___request
		pea	20:W
		jbsr	_exit
L4:		subql	#1,d2
		bne	L5
L3:		moveml	sp@+,d2/d3/a2/a3/a6
		rts

		.even
		.globl	___exitlibraries
___exitlibraries:
		moveml	d2/a2/a6,sp@-
		movel	"A4(_SysBase)",a6
		lea	"A4(___LIB_LIST__)",a2
		movel	a2@+,d2
		beq	L0
L2:		movel	a2@+,a1
		movel	a1@,d0
		jeq	L1
|		clrl	a1@
		movel	d0,a1
		jsr	a6@(-414:W)		| CloseLibrary()
L1:		subql	#1,d2
		bne	L2
L0:		moveml	sp@+,d2/a2/a6
		rts
");

#else
#include <proto/exec.h>

extern struct lib /* These are the elements pointed to by __LIB_LIST__ */
{ struct Library *base;
  char *name;
} *__LIB_LIST__[];

extern void __request(const char *text);
extern ULONG __oslibversion;
extern void exit(int returncode);

extern void writeone(void);
asm(".text;.even;_writeone:;moveb d0,a3@+;rts"); /* Hmmm... */

void __initlibraries(void)
{
  ULONG version=__oslibversion;
  struct lib **list=__LIB_LIST__;
  ULONG numbases=(ULONG)*list++;

  if(numbases)
    do
    {
      struct lib *l=*list++;
      if((l->base=OpenLibrary(l->name,version))==NULL)
      {
        char buf[60];
        ULONG a[2];
        a[0]=version;
        a[1]=(ULONG)l->name;
        RawDoFmt((char *)needtext,a,&writeone,buf);
        __request(buf);
        exit(20);
      }
    }while(--numbases);
}

void __exitlibraries(void)
{
  struct lib **list=__LIB_LIST__;
  ULONG numbases=(ULONG)*list++;

  if(numbases)
    do
    {
      struct lib *l=*list++;
      struct Library *lb=l->base;
      if(lb!=NULL)
      {
        /* l->base=NULL; */
        CloseLibrary(lb);
      }
    }while(--numbases);
}

#endif

ADD2INIT(__initlibraries,-60);
ADD2EXIT(__exitlibraries,-60);
