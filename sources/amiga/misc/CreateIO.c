#include <exec/io.h>
#include <exec/memory.h>
#include <clib/alib_protos.h>
#include <proto/exec.h>
#include <stabs.h>

struct IORequest *CreateExtIO(struct MsgPort *port,long iosize)
{
  struct IORequest *ioreq=NULL;

  if (port && (ioreq=AllocMem(iosize,MEMF_CLEAR|MEMF_PUBLIC)))
  {
    ioreq->io_Message.mn_Node.ln_Type=NT_MESSAGE;
    ioreq->io_Message.mn_ReplyPort=port;
    ioreq->io_Message.mn_Length=iosize;
  }
  return ioreq;
}

struct IOStdReq *CreateStdIO(struct MsgPort *port)
{
  return (struct IOStdReq *)CreateExtIO(port,sizeof(struct IOStdReq));
}

void DeleteExtIO(struct IORequest *ioreq)
{
  int i;

  i=-1;
  ioreq->io_Message.mn_Node.ln_Type=i;
  ioreq->io_Device=(struct Device *)i;
  ioreq->io_Unit=(struct Unit *)i;
  FreeMem(ioreq,ioreq->io_Message.mn_Length);
}

ALIAS(DeleteStdIO,DeleteExtIO);
