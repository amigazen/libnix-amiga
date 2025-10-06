#include <devices/inputevent.h>
#include <proto/exec.h>

void FreeIEvents(volatile struct InputEvent *events)
{
  struct InputEvent *next;
 
  while(events!=NULL)
  {
    next=events->ie_NextEvent;
    FreeMem((APTR)events,sizeof(struct InputEvent));
    events=next;
  }
}
