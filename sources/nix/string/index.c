/*
 * index - find first occurrence of a character in a string
 * 
 * This implementation is based on Henry Spencer's public domain string library
 * which provides V7 compatibility.
 */

#include <string.h>

#define	NULL	0

char *index(const char *s, int charwanted)
{
	extern char *strchr(const char *, int);

	return(strchr(s, charwanted));
}
