#include "_sh.h"

static int builtin_cd(char *path, char *program);
static int cd_helper(char *go_here, char *program, int *changed);
static int builtin_env(void);
static int builtin_exit(char *code, char *input, char **cmd);
static int builtin_setenv(char *name, char *value);
static int builtin_unsetenv(char *name);

/**
 * builtin - manages built-in functions & calls them upon matching input
 * @command[0]: command to be verified against list of built-in functions
 * @command[1]: argument to built-in
 * @input: CLI input to be passed to a function call, if necessary
 * @command: argument vector parsed from input, to be freed when passed to exit
 * @program: program name
 * Return: 1 if function called, else 0
 */

int builtin(char *input, char **command, char *program)
{
	int match = 0;

	if (command[0])
	{
		if (!_strcmp(command[0], "cd"))
			builtin_cd(command[1], program), match = 1;
		else if (!_strcmp(command[0], "env"))
			builtin_env(), match = 1;
		else if (!_strcmp(command[0], "exit"))
			builtin_exit(command[1], input, command), match = 1;
		else if (!_strcmp(command[0], "setenv"))
			builtin_setenv(command[1], command[2]), match = 1;
		else if (!_strcmp(command[0], "unsetenv"))
			builtin_unsetenv(command[1]), match = 1;
	}
	return (match);
}

/**
 * builtin_cd - changes current working directory
 * @path: desired destination working directory
 * @program: program name
 * Return: 0 upon success, -1 otherwise
 */

static int builtin_cd(char *path, char *program)
{
	char *home = NULL, *oldpwd = NULL, cwd[MAX_LEN];
	int changed = 0;

	if (!getcwd(cwd, MAX_LEN))
		return (-1);
	if (path)
	{
		if (_strlen(path) == 1 && path[0] == '-')
		{
			oldpwd = _getenv("OLDPWD");
			if (oldpwd)
				cd_helper(oldpwd, program, &changed),
				printf("%s\n", oldpwd);
			else
				printf("%s\n", cwd);
			free(oldpwd), oldpwd = NULL;
		}
		else
			cd_helper(path, program, &changed);
	}
	else
	{
		home = _getenv("HOME");
		if (home)
			cd_helper(home, program, &changed);
		free(home), home = NULL;
	}
	return (changed ? 0 : -1);
}

/**
 * cd_helper - performs chdir & error handling for builtin_cd
 * @go_here: desired working directory
 * @program: program name
 * @changed: indicates directory changed successfully
 * Return: 0 upon success, -1 if getcwd fails or dir unable to be changed
*/

static int cd_helper(char *go_here, char *program, int *changed)
{
	struct stat buffer;
	char hold_pwd[MAX_LEN];

	if (!getcwd(hold_pwd, MAX_LEN))
		return (-1);
	if (lstat(go_here, &buffer) != -1)
	{
		if (!chdir(go_here))
			builtin_setenv("OLDPWD", hold_pwd),
			getcwd(hold_pwd, MAX_LEN),
			builtin_setenv("PWD", hold_pwd),
			*changed = 1;
	}
	else
		fprintf(stderr, "%s: 1: cd: can't cd to %s\n", program, go_here);
	return (*changed ? 0 : -1);
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

/**
 * builtin_setenv - built-in provision for setenv command
 * @name: name of environmental variable to be set value
 * @value: value to be assigned to named environmental variable
 * Return: 0 upon success, -1 upon memory allocation failure
 */

static int builtin_setenv(char *name, char *value)
{
	size_t iter = 0;
	char *value_str = NULL, **env_cpy = NULL;

	if (!name || !value)
		return (-1);
	for (; data.env_list[iter]; iter++)
		if (!_strncmp(data.env_list[iter], name, _strlen(name)))
			break;
	value_str = malloc(sizeof(char) * (_strlen(name) + _strlen(value) + 2));
	if (!value_str)
		return (-1);
	_strcpy(value_str, name);
	_strcat(value_str, "=");
	_strcat(value_str, value);
	if (data.env_list[iter])
		_strcpy(data.env_list[iter], value_str);
	else
	{
		env_cpy = _realloc(
			(char *)data.env_list,
			(iter) * sizeof(char *),
			(iter + 2) * sizeof(char *));
		if (!env_cpy)
			return (-1);
		_memcpy((char *)env_cpy, (char *)environ, iter * sizeof(char *));
		data.env_list_size++;
		env_cpy[iter] = _strdup(value_str);
		env_cpy[iter + 1] = NULL;
		data.env_list = environ = env_cpy;
	}
	free(value_str), value_str = NULL;
	return (0);
}

/**
 * builtin_unsetenv - built-in provision for unsetenv command
 * @name: name of environmental variable to be set value
 * Return: 0 upon success, -1 upon no variable name input
 */

static int builtin_unsetenv(char *name)
{
	char **env_var = NULL, **shrink = NULL, *tmp = NULL;
	size_t var_len = 0, iter = 0;

	if (!name)
		return (-1);
	for (env_var = data.env_list, var_len = _strlen(name); *env_var; iter++)
	{
		if (!_strncmp(*env_var, name, var_len) && (*env_var)[var_len] == '=')
		{
			tmp = *env_var;
			shrink = env_var;
			do
				shrink[0] = shrink[1];
			while (*shrink++);
			if (iter >= data.env_size)
				free(tmp);
		}
		else
			++env_var;
	}
	return (0);
}
