#include <exec/memory.h>
#include <dos/dosextens.h>
#include <dos/dostags.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stabs.h>

/* Sorry, but the assembler code produced by gcc for this function is too bad.
 * This one is much better!
 */
#ifdef CreateNewProcTags
#undef CreateNewProcTags
static struct Process *createnewproctags(ULONG Tag1,...)
{ return CreateNewProc((struct TagItem *)&Tag1); }
#define CreateNewProcTags createnewproctags
#endif

extern struct WBStart *_WBenchMsg;
extern char *__commandline;
extern struct DosLibrary *DOSBase;
extern struct ExecBase *SysBase;
extern void *__SaveSP;
extern char __dosname[];

extern char *__procname;
extern long __priority;
extern unsigned long __stack;

/* I must close a library after my child is running -
 * and closing a library requires a working dispatcher (IMHO).
 * Also semaphores are much smarter ;). Therefore:
 */
static struct SignalSemaphore *sem;

void __initdetach(void)
{ 
  if(_WBenchMsg!=NULL)
    return;

  if(sem!=NULL)           /* I must be the child process */
  { 
    ObtainSemaphore(sem); /* Assert that my parent is already dead */
    ReleaseSemaphore(sem);
    FreeMem(sem,sizeof(struct SignalSemaphore));
    return;
  }
                          /* I must be the parent */
  if((sem=(struct SignalSemaphore *)
         AllocMem(sizeof(struct SignalSemaphore),MEMF_PUBLIC|MEMF_CLEAR))!=NULL)
  { 
    InitSemaphore(sem);
    
    if((DOSBase=(struct DosLibrary *)OpenLibrary(__dosname,37))!=NULL)
    { 
      struct CommandLineInterface *cli;
      void *stack;

      cli=Cli();
      
      stack=__SaveSP;

      ObtainSemaphore(sem); /* Assert that my child is suspended until I'm finished */
    
        if(CreateNewProcTags(NP_Seglist,cli->cli_Module, /* child process gets my seglist */
                             NP_FreeSeglist,1,           /* and must free it */
                             NP_Cli,1,                   /* it must be a CLI process */
                             NP_StackSize,__stack,       /* it gets a stack */
                             NP_Name,(ULONG)__procname,  /* a name */
                             NP_Priority,__priority,     /* a priority */
                             NP_Arguments,(ULONG)__commandline,/* and my commandline Arguments */
                             TAG_END)!=NULL)
        { cli->cli_Module=0;            /* I'm no longer owner of this */
          CloseLibrary((struct Library *)DOSBase);
          DOSBase=NULL;

          /* Adjust stack, release semaphore and return 0 in one.
           * Maybe the 3 movel are a bit too cautious, but they ARE working
           */
          asm("movel %0,sp;movel %1,a6;movel %2,a0;moveql #0,d0;jmp a6@(-570)"::
              "r"(stack),"r"(SysBase),"r"(sem):"sp","a6","a0");
        }

      ReleaseSemaphore(sem); /* Again only caution - you never know */

      CloseLibrary((struct Library *)DOSBase);
    }
    FreeMem(sem,sizeof(struct SignalSemaphore)); /* Couldn't start child :( */
  }
  exit(20);
}
  
ADD2INIT(__initdetach,-70); /* A very high priority */
