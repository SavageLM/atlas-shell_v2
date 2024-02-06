#include "_sh.h"

/**
 * free_command - frees memory related to command vector created in main
 * @command: command argument vector
 */

void free_command(char **command)
{
	int iter = 0;

	for (; command[iter]; iter++)
		command[iter] = NULL;
	if (*command)
		free(*command), *command = NULL;
}
