#include "_sh.h"

/**
 * free_cmd_dt - frees memory related to command vector created in main
 */

void free_cmd_dt(void)
{
	c_list *hold = NULL;
	int iter = 0;

	if (cmd_dt.commands)
	{
		for (; cmd_dt.commands; cmd_dt.commands = hold)
		{
			hold = cmd_dt.commands->next;
			for (iter = 0; cmd_dt.commands->command[iter]; iter++)
				if (cmd_dt.commands->command[iter])
					free(cmd_dt.commands->command[iter]);
			if (cmd_dt.commands->cmd_str)
				free(cmd_dt.commands->cmd_str), cmd_dt.commands->cmd_str = NULL;
			if (cmd_dt.commands)
				free(cmd_dt.commands), cmd_dt.commands = NULL;
		}
	}
	if (cmd_dt.input)
		free(cmd_dt.input), cmd_dt.input = NULL;
}

/**
 * free_strv - frees memory related to string vector
 * @strv: string vector
 */

void free_strv(char **strv)
{
	int iter = 0;

	for (; strv[iter]; iter++)
		strv[iter] = NULL;
	if (*strv)
		free(*strv), *strv = NULL;
}
