/*
 * getopt() - Return the next user option on each iteration.
 * This is a clone of the usual UNIX getopt() function.
 *
 * This implementation is based on Daniel J. Barrett's public domain
 * GetOpt-1.3 implementation, adapted for libnix-amiga.
 *
 * License: This code is placed in the Public Domain.
 */

#include <stdio.h>
#include <string.h>

/*
 * Some constants.
 */
#define	DASH		'-'	/* This precedes an option. */
#define	ARG_COMING	':'	/* In the option string, this indicates that
				 * that the option requires an argument. */
#define	UNKNOWN_OPT	'?'	/* The char returned for unknown option. */

/*
 * Internal error codes.
 */
#define	ERROR_BAD_OPTION	1
#define	ERROR_MISSING_ARGUMENT	2

/*
 * ANSI function prototypes.
 */
static int	NextOption(char *argv[], char *optString);
static int	RealOption(char *argv[], char *str, int *skip, int *ind,
			     int opt);
static int	HandleArgument(char *argv[], int *optind, int *skip);
static void	Error(int err, int c);
static void	Pass(char *argv[], int *optind, int *optsSkipped);

/*
 * Global variables.  You must declare these externs in your program
 * if you want to see their values!
 */
	
char	*optarg	= NULL;	/* This will point to a required argument, if any. */
int	optind	= 1;	/* The index of the next argument in argv. */
int	opterr	= 1;	/* 1 == print internal error messages.  0 else. */
int	optopt;		/* The actual option letter that was found. */

int getopt(int argc, char *argv[], char *optString)
{
	optarg = NULL;
	if (optind < argc)		/* More arguments to check. */
		return(NextOption(argv, optString));
	else				/* We're done. */
		return(EOF);
}

/*
 * If the current argument does not begin with DASH, it is not an option.
 * Return EOF.
 * If we have ONLY a DASH, and nothing after it... return EOF as well.
 * If we have a DASH followed immediately by another DASH, this is the
 * special "--" option that means "no more options follow."  Return EOF.
 * Otherwise, we have an actual option or list of options.  Process it.
 */
	
static int NextOption(char *argv[], char *optString)
{
	static int optsSkipped = 0;	/* In a single argv[i]. */
	
	if ((argv[optind][0] == DASH)
	&&  ((optopt = argv[optind][1+optsSkipped]) != '\0'))
	{
		if (optopt == DASH)
		{
			optind++;
			return(EOF);
		}
		else
			return(RealOption(argv, optString, &optsSkipped,
					    &optind, optopt));
	}
	else
		return(EOF);
}

/*
 * At this point, we know that argv[optind] is an option or list of
 * options.  If this is a list of options, *optsSkipped tells us how
 * many of those options have ALREADY been parsed on previous calls
 * to getopt().
 * If the option is not legal (not in optString), complain and return
 * UNKNOWN_OPT.
 * If the option requires no argument, just return the option letter.
 * If the option requires an argument, call HandleArgument and return
 * the option letter.
 */
	
static int RealOption(char *argv[], char *optString, int *optsSkipped,
			int *optind, int optopt)
{
	char *where;	/* Pointer to the letter in optString. */
	int argWasOK;	/* An indication that a required arg was found. */

	(*optsSkipped)++;

	if (optopt == ARG_COMING)	/* Special case of "-:" */
	{
		Error(ERROR_BAD_OPTION, optopt);
		Pass(argv, optind, optsSkipped);
		return(UNKNOWN_OPT);
	}

	else if ((where = strchr(optString, optopt)) != NULL)
	{
		argWasOK = 1;	/* Assume any argument will be found. */

		if (*(where+1) == ARG_COMING)
			argWasOK = HandleArgument(argv, optind, optsSkipped);

		Pass(argv, optind, optsSkipped);

		return(argWasOK ? optopt : UNKNOWN_OPT);
	}

	else
	{
		Error(ERROR_BAD_OPTION, optopt);
		Pass(argv, optind, optsSkipped);
		return(UNKNOWN_OPT);
	}
}

/*
 * We have an option in argv[optind] that requires an argument.  If there
 * is no whitespace after the option letter itself, take the rest of
 * argv[optind] to be the argument.
 * If there IS whitespace after the option letter, take argv[optind+1] to
 * be the argument.
 * Otherwise, if there is NO argument, complain!
 * Return 1 on success, 0 on error.
 */

static int HandleArgument(char *argv[], int *optind, int *optsSkipped)
{
	int OK;

	if (argv[*optind][1+(*optsSkipped)])
	{
		optarg = argv[*optind] + 1 + (*optsSkipped);
		OK = 1;
	}
	else if (argv[(*optind)+1])
	{
		optarg = argv[(*optind)+1];
		(*optind)++;
		OK = 1;
	}
	else
	{
		Error(ERROR_MISSING_ARGUMENT, optopt);
		OK = 0;
	}

	(*optsSkipped) = 0;
	(*optind)++;
	return(OK);
}

/*
 * Print an appropriate error message.
 */

static void Error(int err, int c)
{
	if (opterr)
	{
		fprintf(stderr, "-%c: ", c);
		switch (err)
		{
			case ERROR_BAD_OPTION:
				fprintf(stderr, "Illegal option.\n");
				break;
			case ERROR_MISSING_ARGUMENT:
				fprintf(stderr,
				  "An argument is required, but missing.\n");
				break;
			default:
				fprintf(stderr,
				  "An unknown error occurred.\n");
				break;
		}
	}
}

/*
 * We have reached the end of argv[optind]... there are no more options
 * in it to parse.  Skip to the next item in argv.
 */

static void Pass(char *argv[], int *optind, int *optsSkipped)
{
	if (argv[*optind]
	&&  (argv[*optind][0] == DASH)
	&&  (argv[*optind][1+(*optsSkipped)] == '\0'))
	{
		(*optind)++;
		(*optsSkipped) = 0;
	}
}
