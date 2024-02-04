#include "header/_sh.h"

/**
 * separator - splits/tokenizes input string per delimiter(s)
 * @input: input string
 * @delim: delimiter(s) by which input is to be divided
 * Return: non-empty tokenized segment from input string, NULL otherwise
 */

char *separator(char **input, char *delim)
{
	char *extract_str = NULL;

	while ((extract_str = strsep(input, delim)) && !*extract_str)
		;
	return (extract_str);
}
