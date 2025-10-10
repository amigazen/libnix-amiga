/*
 * memccpy - copy bytes up to a certain char
 * 
 * This implementation is based on Henry Spencer's public domain string library.
 * CHARBITS should be defined only if the compiler lacks "unsigned char".
 * It should be a mask, e.g. 0377 for an 8-bit machine.
 */

#include <string.h>

#define	NULL	0

#ifndef CHARBITS
#	define	UNSCHAR(c)	((unsigned char)(c))
#else
#	define	UNSCHAR(c)	((c)&CHARBITS)
#endif

void *memccpy(void *dst, const void *src, int ucharstop, size_t size)
{
	char *d;
	const char *s;
	size_t n;
	int uc;

	if (size <= 0)
		return(NULL);

	s = (const char *)src;
	d = (char *)dst;
	uc = UNSCHAR(ucharstop);
	for (n = size; n > 0; n--)
		if (UNSCHAR(*d++ = *s++) == uc)
			return(d);

	return(NULL);
}
