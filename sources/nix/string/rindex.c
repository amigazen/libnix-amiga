/*
 * rindex - find last occurrence of a character in a string
 * 
 * This implementation is based on Henry Spencer's public domain string library
 * which provides V7 compatibility.
 */

#include <string.h>

#define	NULL	0

char *rindex(const char *s, int charwanted)
{
	extern char *strrchr(const char *, int);

	return(strrchr(s, charwanted));
}
