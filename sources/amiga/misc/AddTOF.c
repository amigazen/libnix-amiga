#include <exec/interrupts.h>
#include <hardware/intbits.h>
#include <graphics/graphint.h>
#include <clib/alib_protos.h>
#include <proto/graphics.h>
#include <proto/exec.h>

static int stub()
{
  register struct Isrvstr *intr asm("a1");

  (*intr->ccode)(intr->Carg); return 0;
}

void AddTOF(struct Isrvstr *intr, long (*code)(), long arg)
{
   intr->Iptr=intr;
   intr->code=(int (*)())stub;
   intr->ccode=(int (*)())code;
   intr->Carg=(int)arg;
   AddIntServer(INTB_VERTB,(struct Interrupt *)intr);
}

void RemTOF(struct Isrvstr *intr)
{
  RemIntServer(INTB_VERTB,(struct Interrupt *)intr);
}
