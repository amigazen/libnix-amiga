#include <libraries/commodities.h>
#include <proto/commodities.h>

CxObj *HotKey(STRPTR description, struct MsgPort *port, long id)
{
  CxObj *filter;

  if ((filter=CreateCxObj(CX_FILTER,(long)description,NULL)))
  {
    AttachCxObj(filter, CreateCxObj(CX_SEND, (long)port, id));
    AttachCxObj(filter, CreateCxObj(CX_TRANSLATE, NULL, NULL));
    if (CxObjError(filter))
    {
      DeleteCxObjAll(filter); filter=NULL;
    }
  }
  return filter;
}
