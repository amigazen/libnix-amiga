/*
 * memcpy - copy bytes
 * 
 * This implementation is based on Henry Spencer's public domain string library
 * which properly handles overlapping memory regions as required by X3J11.
 */

#include <string.h>

void *memcpy(void *dst, const void *src, size_t size)
{
	char *d;
	const char *s;
	size_t n;

	if (size <= 0)
		return(dst);

	s = (const char *)src;
	d = (char *)dst;
	if (s <= d && s + (size-1) >= d) {
		/* Overlap, must copy right-to-left. */
		s += size-1;
		d += size-1;
		for (n = size; n > 0; n--)
			*d-- = *s--;
	} else
		for (n = size; n > 0; n--)
			*d++ = *s++;

	return(dst);
}
