#include "_sh.h"

static int check_PATH_PWD(void);
static char **PATH_processing(char *command);
static int PATH_str_mem_calc(char *PATH_str, char *command);
static char **remove_colons(char *chop);
static char **concat_slash_command(char **paths, char *command);
static int fork_execute(char *input, char *name, char **cmd);

/**
 * launch_manager - manages input cmd, filtering through builtin & access, then
 *         calling fork_execute if program exists & can be accessed
 * @input: CLI input
 * @cmd: vector of arguments retrieved from input
 * @program: program name
 * Return: 0 success, 1 built-in called, otherwise respective err no.
 */

int launch_manager(char *input, char **cmd, char *program)
{
	int iter = 0, tag = 0, problem = 0;
	char **full_paths = NULL;

	problem = check_PATH_PWD();
	if (builtin(input, cmd, program))
		return (1);
	if (access(cmd[0], F_OK) == -1)
	{
		if (problem == 1)
			return (127);
		full_paths = PATH_processing(cmd[0]);
		if (!full_paths)
			return (127);
		for (iter = 0; full_paths[iter]; iter++)
			if (!access(full_paths[iter], X_OK))
			{
				fork_execute(input, full_paths[iter], cmd), tag = 1;
				break;
			}
		for (iter = 0; full_paths[iter]; iter++)
			free(full_paths[iter]), full_paths[iter] = NULL;
		free(full_paths);
	}
	else
	{
		if (!access(cmd[0], X_OK))
		{
			if (problem == 1 && cmd[0][0] != '/')
				return (127);
			fork_execute(input, cmd[0], cmd), tag = 1;
		}
		else if (!access(cmd[0], F_OK) && access(cmd[0], X_OK) == -1)
			return (13);
	}
	return (!tag ? 127 : 0);
}

/**
 * check_PATH_PWD - checks status of PATH & PWD environmental variables
 * Return: 0 if PATH & PWD, 1 if PATH NULL, 2 if PWD NULL
 */

static int check_PATH_PWD(void)
{
	char *check_PATH = NULL, *check_PWD = NULL;

	check_PATH = _getenv("PATH");
	if (!check_PATH)
	{
		free(check_PATH), check_PATH = NULL;
		return (1);
	}
	if (check_PATH)
		free(check_PATH), check_PATH = NULL;
	check_PWD = _getenv("PWD");
	if (!check_PWD)
	{
		free(check_PWD), check_PWD = NULL;
		return (2);
	}
	if (check_PWD)
		free(check_PWD), check_PWD = NULL;
	return (0);
}

/**
 * PATH_processing - processes PATH env var for stat/access use
 * @command: command to be appended with slash to individual PATH directories
 * Return: processed PATH elements for use in launch_manager function, NULL
 *         upon malloc failure, input vector unavailable, or PATH variable
 *         empty/unaccessible
 */

static char **PATH_processing(char *command)
{
	int mem_size = 0;
	char *PATH_str = NULL, *del = NULL, **paths = NULL, **search_paths = NULL;

	if (!command)
		return (NULL);
	PATH_str = _getenv("PATH");
	if (!PATH_str)
		return (NULL);
	mem_size = PATH_str_mem_calc(PATH_str, command);
	del = malloc(sizeof(char) * mem_size);
	if (!del)
		return (NULL);
	_strcpy(del, PATH_str);
	paths = remove_colons(del);
	search_paths = concat_slash_command(paths, command);
	free(paths), free(del), free(PATH_str);
	return (search_paths);
}

/**
 * PATH_str_mem_calc - calculates memory to be allocated when handling PATH
 * @PATH_str: input string suspected to contain colons
 * @command: input command from main, necessary for calculation
 * Return: multiplier number for mem alloc calculation
 */

static int PATH_str_mem_calc(char *PATH_str, char *command)
{
	int iter = 0, bytes = 0;

	for (; PATH_str[iter]; iter++)
		if (PATH_str[iter] == ':')
			bytes++;
	bytes++;
	bytes *= (_strlen(command) + 1);
	bytes += (_strlen(PATH_str) + 1);
	return (bytes);
}

/**
 * remove_colons - divides input string into several based on colons present
 * @colon_str: input string to be divided
 * Return: populated string vector upon success, NULL upon mem alloc failure
 */

static char **remove_colons(char *colon_str)
{
	int iter = 0;
	char *copy = NULL, **paths = NULL;

	if (!colon_str)
		return (NULL);
	paths = malloc(sizeof(char *) + MAX_LEN);
	if (!paths)
		return (NULL);
	for (copy = colon_str; (paths[iter] = separator(&copy, ":")); iter++)
		;
	return (paths);
}

/**
 * concat_slash_command - concatenates slash + command to all strings in paths
 *                        vector
 * @paths: input vector, to all elements of which slash + command appended
 * @command: command from main
 * Return: strings concatenated with slash followed by input cmd
 */

static char **concat_slash_command(char **paths, char *command)
{
	int iter = 0;
	char slash_str[MAX_LEN] = "/", *slash_command = NULL, *path = NULL;
	char **result = NULL;

	if (!paths || !command)
		return (NULL);
	result = _calloc(sizeof(char *) + MAX_LEN, 1);
	if (!result)
		return (NULL);
	slash_str[0] = '/', slash_str[1] = '\0';
	slash_command = _strcat(slash_str, command);
	for (; paths[iter]; iter++)
	{
		path = str_concat(paths[iter], slash_command);
		result[iter] = _strdup(path);
		free(path), path = NULL;
	}
	return (result);
}

/**
 * fork_execute - launches input command with its arguments
 * @input: command
 * @name: command name used for error messages
 * @cmd: arguments to the command
 * Return: 1 upon success, -1 if input or cmd NULL
 */

static int fork_execute(char *input, char *name, char **cmd)
{
	pid_t launch = 0;
	int status = 0, flag = 0;

	if (!input || !cmd)
		return (-1);
	launch = fork();
	if (launch == -1)
		perror(name), exit(EXIT_FAILURE);
	else if (launch == 0)
	{
		if (execve(name, cmd, environ) == -1)
			perror(name), free(input), exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(launch, &status, 0);
		flag = WEXITSTATUS(status);
		if (flag == 2 && !isatty(STDIN_FILENO))
			free_command(cmd), free(input), input = NULL, _exit(flag);
	}
	return (1);
}
