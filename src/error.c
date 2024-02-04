#include "header/_sh.h"

static void error_13(char *cmd, char *program);
static void error_127(char *command, char *program);

/**
 * error_processor - processes errors suitably respective to error code
 * @cmd: command vector
 * @program: name of shell application
 * @input: CLI input
 * @code: error code
*/

void error_processor(char **cmd, char *program, char *input, int code)
{
	if (code == 13)
		error_13(cmd[0], program);
	else if (code == 127)
		error_127(cmd[0], program);
	if (!isatty(STDIN_FILENO))
		free_command(cmd), free(input), input = NULL, exit(code);
}

/**
 * error_13 - prints code 13 error message to stderr
 * @command: command that has been denied permission
 * @program: name of program
 */

static void error_13(char *command, char *program)
{
/*	fprintf(stderr, "%s: 1: %s: Permission denied\n", prog, command);*/
	(void)program;
	perror(command);
}

/**
 * error_127 - prints code 127 error message to stderr
 * @command: command that is not found
 * @program: name of program
 */

static void error_127(char *command, char *program)
{
	fprintf(stderr, "%s: 1: %s: not found\n", program, command);
}
