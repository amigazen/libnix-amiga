
/*
 * intl_dgettext.c - dgettext implementation
 * Simple stub that returns the original message
 */

char *dgettext(const char *domainname __attribute__((unused)), const char *msg)
{
	return((char *) msg );
}
