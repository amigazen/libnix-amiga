/*
 * bcmp - Berkeley equivalent of memcmp
 * 
 * This implementation is based on Henry Spencer's public domain string library
 * which provides Berkeley compatibility.
 */

#include <string.h>

int bcmp(const void *s1, const void *s2, size_t length)
{
	return(memcmp(s1, s2, length));
}
