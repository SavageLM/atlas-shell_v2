#include "_sh.h"

static void signal_SIGINT(int sig);
static ssize_t prompt(char *prompt_str, char **input, size_t *len);
static int empty_input(char *input);

p_dt prog;
c_dt cmd_dt;

/**
 * main - infinite loop responsible for prompt, calling parse/launch functions,
 *        & error messages, if necessary
 * @argc: argument count, unused
 * @argv: vector of arguments passed on run
 * Return: 0, always
 */

int main(int __attribute__((unused)) argc, char **argv)
{
	size_t input_len = 0;
	int prompt_ret = 0;

	prog.program = argv[0];
	while (1)
	{
		cmd_dt.cmd_count = 0, cmd_dt.op_count = 0, cmd_dt.op_index = 0;
		signal(SIGINT, signal_SIGINT);
		prompt_ret = prompt("# ", &cmd_dt.input, &input_len);
		if (prompt_ret < 0)
			continue;
		parser(cmd_dt.input);
		launcher(cmd_dt.commands);
		free_cmd_dt();
		fflush(stdout);
	}
	return (0);
}

/**
 * env_load - allocates memory for env_list (adjustable copy of environ)
 * Return: 0 upon success, -1 upon memory allocation failure
*/

int __attribute__ ((constructor)) env_load(void)
{
	size_t size = 0/* , iter = 0 */;

	if (environ)
	{
		for (; environ[size]; size++)
			;
		prog.env_list = _calloc(sizeof(char *) * (size + 1), 1);
		if (!prog.env_list)
			return (-1);
		_memcpy((char *)prog.env_list, (char *)environ, size * sizeof(char *));
		prog.env_list_size = prog.env_size = size;
	}
	return (0);
}

/**
 * env_free - frees memory related to env_list (adjustable copy of environ)
*/

void __attribute__ ((destructor)) env_free(void)
{
	size_t added = 0;

	if (prog.env_list_size > prog.env_size)
		for (added = prog.env_size; prog.env_list[added]; added++)
			free(prog.env_list[added]), prog.env_list[added] = NULL;
	if (prog.env_list)
		free(prog.env_list);
}

/**
 * signal_SIGINT - defines instructions upon SIGINT, as input to signal
 * @sig: input signal
 */

static void signal_SIGINT(int sig)
{
	if (sig == SIGINT)
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n# ", 3);
}

/**
 * prompt - gets line from input and maintains prompt
 * @prompt_str: How we want the prompt to look
 * @input: input received from stdin
 * @len: the length of the input from stdin
 * Return: the number of characters read,
 *         -1 upon single line break,
 *         -2 if input is empty
 */

static ssize_t prompt(char *prompt_str, char **input, size_t *len)
{
	ssize_t getline_out = 0, error = 0;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, prompt_str, _strlen(prompt_str));
	getline_out = getline(input, len, stdin);
	if (getline_out == EOF)
		free(*input), exit(0);
	else if (!getline_out)
		return (-1);
	if (empty_input(*input))
		error = -2, free(*input), *input = NULL;
	return (!error ? getline_out : error);
}

/**
 * empty_input - verifies if input is only space characters
 * @input: input string
 * Return: 0 if length of string equal to number of whitespaces, -1 otherwise
 */

static int empty_input(char *input)
{
	int iter = 0, spaces = 0;

	if (input)
		for (; input[iter]; iter++)
			if (
				input[iter] == ' ' ||
				input[iter] == '\t' ||
				input[iter] == '\n' ||
				input[iter] == '\r'
			)
				spaces++;
	return (spaces == _strlen(input) ? 1 : 0);
}
