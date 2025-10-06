#include <clib/alib_protos.h>
#include <proto/graphics.h>

void waitbeam(long pos)
{
  do {} while(pos>VBeamPos());
}
