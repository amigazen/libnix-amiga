#ifndef _STRSUP_H /* don't include this twice */

#define _STRSUP_H

#if defined(__GNUC__) && defined(__OPTIMIZE__)

extern __inline__ void *memcpy(void *s1,const void *s2,size_t n)
{
  register char *a6 __asm("a6") = *(char **)4;
  register const void *a0 __asm("a0") = s2;
  register const void *a1 __asm("a1") = s1;
  register size_t d0 __asm("d0") = n;
  __asm __volatile ("jsr a6@(-0x270)"
  : /* no output */
  : "r" (a6), "r" (a0), "r" (a1), "r" (d0)
  : "a0","a1","d0","d1", "memory");

  return s1;
}

extern __inline char *strcat(char *s1,const char *s2)
{ 
  char *s=s1;

  while(*s++)
    ;
  --s;
  while((*s++=*s2++))
    ;
  return s1;
}

extern __inline char *strcpy(char *s1,const char *s2)
{ char *s=s1;
  do
    *s++=*s2;
  while(*s2++!='\0');
  return s1;
}

extern __inline size_t strlen(const char *string)
{
  const char *s=string;

  while(*s++)
    ;
  return ~(string-s);
}

extern __inline size_t strlen_plus_one(const char *string)
{
  const char *s=string;

  while(*s++)
    ;
  return (s-string);
}

#else

#define strlen_plus_one(s) strlen(s)+1 /* not gnu :( */

#endif
#endif
