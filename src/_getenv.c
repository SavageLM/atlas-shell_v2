#include "_sh.h"

/**
 * _getenv - custom getenv function, retrieves env var value
 * @var_name: name of environmental variable to be retrieved
 * Return: requested environmental variable value
 */

char *_getenv(char *var_name)
{
	int iter = 0, found = 0, var_def = 0;
	char *var_eq, *capture = NULL, *env_var = NULL, *env_copy = NULL;
	char *value_str = NULL;
	char *split[MAX_LEN] = { NULL };

	if (!var_name)
		return (NULL);
	var_eq = str_concat(var_name, "=");
	/*Looping through environment list to find match for env variable*/
	for (iter = 0, var_def = _strlen(var_eq); prog.env_list[iter]; iter++)
		if (!_strncmp(prog.env_list[iter], var_eq, var_def))
		{
			capture = prog.env_list[iter], found = 1;
			break;
		}
	if (found)
	{
		if (_strlen(capture) != var_def)
		{
			env_var = _strdup(capture), capture = NULL;
			/* Looping through env_var to seperate based on "="*/
			for (iter = 0, env_copy = env_var;
				(split[iter] = separator(&env_copy, "=")); iter++)
				;
			value_str = _strdup(split[1]);
			free(env_var), env_var = NULL;
		}
		free_strv(split);
	}
	free(var_eq), var_eq = NULL;
	/*Free all allocated memory no longer needed before return*/
	return (value_str ? value_str : NULL);
}
