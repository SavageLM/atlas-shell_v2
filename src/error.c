#include "_sh.h"

static void error_13(char *cmd);
static void error_127(char *command);

/**
 * error_processor - processes errors suitably respective to error code
 * @cmd: command vector
 * @code: error code
*/

void error_processor(char **cmd, int code)
{
	if (code == 13)
		error_13(cmd[0]);
	else if (code == 127)
		error_127(cmd[0]);
	if (!isatty(STDIN_FILENO) && cmd_dt.op_array[cmd_dt.op_index] != 0x4)
	{
		if (cmd_dt.op_count && cmd_dt.op_array[cmd_dt.op_index] != 0x2)
			code = 0;
		free_cmd_dt(), exit(code);
	}
}

/**
 * error_13 - prints code 13 error message to stderr
 * @command: command that has been denied permission
 */

static void error_13(char *command)
{
/*	fprintf(stderr, "%s: 1: %s: Permission denied\n", prog, command);*/
	perror(command);
}

/**
 * error_127 - prints code 127 error message to stderr
 * @command: command that is not found
 */

static void error_127(char *command)
{
	fprintf(stderr, "%s: 1: %s: not found\n", prog.program, command);
}
