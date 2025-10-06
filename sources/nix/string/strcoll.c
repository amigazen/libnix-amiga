#include <locale.h>
#include <libraries/locale.h>
#include <proto/locale.h>
#include <limits.h>

extern struct Locale *__localevec[];

int strcoll(const char *s1,const char *s2)
{ if(__localevec[LC_COLLATE-1]==NULL)
    return strcmp(s1,s2);
  else
    return StrnCmp(__localevec[LC_COLLATE-1],(char *)s1,(char *)s2,LONG_MAX,SC_COLLATE1);
}
