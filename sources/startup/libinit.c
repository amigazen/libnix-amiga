/******************************************************************************/
/*                                                                            */
/* this works with gcc too and makes life easier                              */
/*                                                                            */
/******************************************************************************/

#define _USEOLDEXEC_

/******************************************************************************/
/*                                                                            */
/* includes                                                                   */
/*                                                                            */
/******************************************************************************/

#include <exec/types.h>
#include <exec/resident.h>
#include <proto/exec.h>
#include "libinit.h"
#include "stabs.h"

/******************************************************************************/
/*                                                                            */
/* *** FIRST *** function - prevents a crash when called from CLI!            */
/*                                                                            */
/******************************************************************************/

int safefail()
{
  return -1;
}

/******************************************************************************/
/*                                                                            */
/* imports                                                                    */
/*                                                                            */
/******************************************************************************/

extern const UWORD LibVersion;
extern const UWORD LibRevision;

extern const BYTE LibName[];
extern const BYTE LibIdString[];

extern APTR  __FuncTable__[];

extern int   __UserLibInit(_LIB *);
extern void  __UserLibCleanup();

/******************************************************************************/
/*                                                                            */
/* resident structure                                                         */
/*                                                                            */
/******************************************************************************/

const APTR InitTab[4];

static const struct Resident RomTag = {
  RTC_MATCHWORD,
  (struct Resident *)&RomTag,
  (APTR)((&RomTag)+1),
  RTF_AUTOINIT,
  0,
  NT_LIBRARY,
  0,
  (BYTE *)LibName,
  (BYTE *)LibIdString,
  (APTR)&InitTab
};

/******************************************************************************/
/*                                                                            */
/* autoinit table for use with initial MakeLibrary()                          */
/*                                                                            */
/******************************************************************************/

const APTR InitTab[4] = {
  (APTR)sizeof(_LIB),
  (APTR)&__FuncTable__[1],
  0,
  (APTR)LibInit
};

/******************************************************************************/
/*                                                                            */
/* support function(s) to be inlined                                          */
/*                                                                            */
/******************************************************************************/

static inline APTR __GetDataSeg()
{
  APTR res;
  asm ("lea ___a4_init,%0" : "=a" (res));
  return res;
}

static inline ULONG __BSize()
{
  ULONG res;
  asm ("movel #___bss_size,%0" : "=d" (res));
  return res;
}

static inline ULONG *__GetBssStart()
{
  ULONG *res;
  asm ("lea __edata,%0" : "=a" (res));
  return res;
}

/******************************************************************************/
/*                                                                            */
/* initialization function called by MakeLibrary()                            */
/*                                                                            */
/******************************************************************************/

struct Library *LibInit()
{
  register APTR DataSeg asm("a4");
  register APTR SegList asm("a0");
  register struct Library *lib asm("d0");
  _LIB *Library = (_LIB *)lib;
  ULONG size;
  int result;

  /* init library base */

  Library->LibNode.lib_Node.ln_Type = NT_LIBRARY;
  Library->LibNode.lib_Node.ln_Name = (UBYTE *)LibName;
  Library->LibNode.lib_Flags        = LIBF_CHANGED | LIBF_SUMUSED;
  Library->LibNode.lib_Version      = (UWORD)LibVersion;
  Library->LibNode.lib_Revision     = (UWORD)LibRevision;
  Library->LibNode.lib_IdString     = (UBYTE *)LibIdString;
  Library->SegList                  = SegList;
  Library->DataSeg                  = __GetDataSeg();

  /* clear the bss part */

  if ((size=__BSize()))
  {
    ULONG *p=__GetBssStart();

    do
    {
      *p++=0;
    }
    while((size-=sizeof(ULONG)));
  }

  DataSeg=Library->DataSeg; asm volatile ("" : /**/ : "r" (DataSeg));

  /* now call user-init */

  result=__UserLibInit(Library);

  /* all ok? */

  if (result!=0)
    Library=NULL;

  /* this will be added to SysBase->LibList or NULL (init error) */

  return (struct Library *)Library;
}

/******************************************************************************/
/*                                                                            */
/* LibOpen() will be called for every OpenLibrary()                           */
/*                                                                            */
/* !!! CAUTION: This function runs in a forbidden state !!!                   */
/*                                                                            */
/******************************************************************************/

struct Library *LibOpen()
{
  register struct Library *lib asm("a6");

  /* clear delayed expunge flag */

  lib->lib_Flags &= ~LIBF_DELEXP;

  /* one new user */

  lib->lib_OpenCnt++;

  /* return basePtr */

  return lib;
}

/******************************************************************************/
/*                                                                            */
/* LibClose() will be called for every CloseLibrary()                         */
/*                                                                            */
/* !!! CAUTION: This function runs in a forbidden state !!!                   */
/*                                                                            */
/******************************************************************************/

APTR LibClose()
{
  register struct Library *lib asm("a6");
  APTR SegList=0;

  /* one less user */

  if (--lib->lib_OpenCnt==0 && (lib->lib_Flags&LIBF_DELEXP))
    SegList=LibExpunge();

  /* SegList or NULL (still in use) */

  return SegList;
}

/******************************************************************************/
/*                                                                            */
/* remove library from memory if possible                                     */
/*                                                                            */
/* !!! CAUTION: This function runs in a forbidden state !!!                   */
/*                                                                            */
/******************************************************************************/

APTR LibExpunge()
{
  register struct Library *lib asm("a6");
  register APTR DataSeg asm("a4");
  _LIB *Library = (_LIB *)lib;
  APTR SegList=0;

  /* set delayed expunge flag */

  Library->LibNode.lib_Flags |= LIBF_DELEXP;

  /* still in use? */

  if (Library->LibNode.lib_OpenCnt == 0)
  {
    ULONG NegSize;

    /* return the seglist for UnLoadSeg() */

    SegList = Library->SegList;

    /* remove library from SysBase->LibList */

    Remove((struct Node *)Library);

    DataSeg=Library->DataSeg; asm volatile ("" : /**/ : "r" (DataSeg));

    /* now call user-exit */

    __UserLibCleanup();

    /* free library */

    NegSize = Library->LibNode.lib_NegSize;
    FreeMem((APTR)((UBYTE *)Library-(UBYTE *)NegSize),NegSize+Library->LibNode.lib_PosSize);
  }
  return SegList;
}

/******************************************************************************/
/*                                                                            */
/* a do nothing stub (required!)                                              */
/*                                                                            */
/******************************************************************************/

APTR LibExtFunc()
{
  return 0;
}

/******************************************************************************/
/*                                                                            */
/* add these functions to 'funclist'                                          */
/*                                                                            */
/******************************************************************************/

ADD2LIST(LibOpen,__FuncTable__,22);
ADD2LIST(LibClose,__FuncTable__,22);
ADD2LIST(LibExpunge,__FuncTable__,22);
ADD2LIST(LibExtFunc,__FuncTable__,22);

/******************************************************************************/
/*                                                                            */
/* end of libinit.c                                                           */
/*                                                                            */
/******************************************************************************/
