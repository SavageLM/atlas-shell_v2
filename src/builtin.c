#include "header/_sh.h"

static int builtin_cd(char *path);
static int builtin_env(void);
static int builtin_exit(char *code, char *input, char **cmd);

/**
 * builtin - manages built-in functions & calls them upon matching input
 * @command[0]: command to be verified against list of built-in functions
 * @command[1]: argument to built-in
 * @input: CLI input to be passed to a function call, if necessary
 * @command: argument vector parsed from input, to be freed when passed to exit
 * Return: 1 if function called, else 0
 */

int builtin(char *input, char **command)
{
	int match = 0;

	if (command[0])
	{
		if (!strcmp(command[0], "cd"))
			builtin_cd(command[1]), match = 1;
		else if (!strcmp(command[0], "env"))
			builtin_env(), match = 1;
		else if (!strcmp(command[0], "exit"))
			builtin_exit(command[1], input, command), match = 1;
	}
	return (match);
}

/**
 * builtin_cd - changes current working directory
 * @path: desired destination working directory
 * Return: 0 upon success, -1 otherwise
 */

static int builtin_cd(char *path)
{
	struct stat buffer;
/*
 *	char *olD = NULL, cwd[MAX_LEN];
 *
 *	(void)input;
 *	(void)command;
 *
 *	if (getcwd(cwd, sizeof(cwd)))
 *		*cwd = '\0';
 *
 *	if (!path)
 *		path = getenvY("HOME");
 *
 * WIP
 *	if (!strcmp("-", command[1]))
 *	{
 *		olD = getenvY("OLDPWD");
 *		if (!olD)
 *		{
 *			printf("%s: cd: OLDPWD not set\n", command[0]);
 *			return (-1);
 *		}
 *		if (chdir("olD"))
 *			printf("%s\n", olD);
 *		return (0);
 *	}
 */
	if (!lstat(path, &buffer))
		chdir(path);
	return (0);
}

/**
 * builtin_env - prints environmental variables
 * Return: 0 upon success, -1 otherwise or if env vars N/A
 */

static int builtin_env(void)
{
	char **env_var = NULL;
	int counter = 0;

	for (env_var = environ; *env_var; ++env_var)
		printf("%s\n", *env_var), counter++;
	return (counter ? 0 : -1);
}

/**
 * builtin_exit - built-in provision for terminal exit upon command
 * @code: exit code, if desired
 * @input: CLI input from main to be freed, if necessary
 * @cmd: argument vector parsed from input, to be freed
 * Return: 0, if exit fails
 */

static int builtin_exit(char *code, char *input, char **cmd)
{
	int status = 0, invalid = 0, iter = 0;

	if (code)
	{
		for (; code[iter]; iter++)
			if (!_isdigit(code[iter]))
			{
				invalid = 1;
				break;
			}
		status = _atoi(code);
	}
	if (invalid || status < 0)
		fprintf(stderr, "./hsh: 1: %s: Illegal number: %s\n", cmd[0], code),
		status = 2;
	if (input)
		free(input);
	free_command(cmd);
	exit(status);
	return (0);
}
