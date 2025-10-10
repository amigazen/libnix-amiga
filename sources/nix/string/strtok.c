/*
 * strtok - Get next token from string s (NULL on 2nd, 3rd, etc. calls),
 * where tokens are nonempty strings separated by runs of
 * chars from delim.  Writes NULs into s to end tokens.  delim need not
 * remain constant from call to call.
 * 
 * This implementation is based on Henry Spencer's public domain string library
 * which provides comprehensive testing and better edge case handling.
 */

#include <string.h>

#define	NULL	0

static char *scanpoint = NULL;

char *strtok(char *s, const char *delim)
{
	char *scan;
	char *tok;
	const char *dscan;

	if (s == NULL && scanpoint == NULL)
		return(NULL);
	if (s != NULL)
		scan = s;
	else
		scan = scanpoint;

	/*
	 * Scan leading delimiters.
	 */
	for (; *scan != '\0'; scan++) {
		for (dscan = delim; *dscan != '\0'; dscan++)
			if (*scan == *dscan)
				break;
		if (*dscan == '\0')
			break;
	}
	if (*scan == '\0') {
		scanpoint = NULL;
		return(NULL);
	}

	tok = scan;

	/*
	 * Scan token.
	 */
	for (; *scan != '\0'; scan++) {
		for (dscan = delim; *dscan != '\0';)	/* ++ moved down. */
			if (*scan == *dscan++) {
				scanpoint = scan+1;
				*scan = '\0';
				return(tok);
			}
	}

	/*
	 * Reached end of string.
	 */
	scanpoint = NULL;
	return(tok);
}
