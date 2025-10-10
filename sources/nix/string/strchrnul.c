/*
 * strchrnul - find first occurrence of a character in a string
 * Returns pointer to the character if found, or pointer to the NUL terminator if not found
 */

#include <string.h>

#ifndef NULL
#define NULL 0
#endif

char *strchrnul(const char *s, int charwanted)
{
    register const char *scan;

    /*
     * The odd placement of the two tests is so NUL is findable.
     * Unlike strchr(), we return a pointer to the NUL terminator
     * if the character is not found, rather than returning NULL.
     */
    for (scan = s; *scan != charwanted;)    /* ++ moved down for opt. */
        if (*scan++ == '\0')
            return (char *)scan;  /* Return pointer to NUL terminator */
    return (char *)scan;  /* Return pointer to found character */
}


