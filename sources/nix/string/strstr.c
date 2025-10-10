/*
 * strstr - find first occurrence of wanted in s
 * 
 * This implementation is based on Henry Spencer's public domain string library
 * which provides better edge case handling and more robust algorithm.
 */

#include <string.h>

char *strstr(const char *s, const char *wanted)
{
	const char *scan;
	size_t len;
	char firstc;
	extern int strncmp(const char *, const char *, size_t);
	extern size_t strlen(const char *);

	/*
	 * The odd placement of the two tests is so "" is findable.
	 * Also, we inline the first char for speed.
	 * The ++ on scan has been moved down for optimization.
	 */
	firstc = *wanted;
	len = strlen(wanted);
	for (scan = s; *scan != firstc || strncmp(scan, wanted, len) != 0; )
		if (*scan++ == '\0')
			return(NULL);
	return((char *)scan);
}
