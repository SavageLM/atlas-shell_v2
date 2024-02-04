#include "header/_sh.h"

static void signal_SIGINT(int sig);
static ssize_t prompt(char *prompt_str, char **input, size_t *len);
static int empty_input(char *input);
static int parse_input(char *input, char *command[], char *delim);

/**
 * main - infinite loop responsible for prompt, calling parse/launch functions,
 *        & error messages, if necessary
 * @argc: argument count, unused
 * @argv: vector of arguments passed on run
 * Return: 0, always
 */

int main(int __attribute__((unused)) argc, char **argv)
{
	char *input = NULL, *command[MAX_LEN] = { NULL };
	size_t input_len = 0;
	int prompt_ret = 0, launch_error = 0;

	while (1)
	{
		signal(SIGINT, signal_SIGINT);
		prompt_ret = prompt("# ", &input, &input_len);
		if (prompt_ret < 0)
			continue;
		parse_input(input, command, SPC_DELIM);
		launch_error = launch_manager(input, command);
		if (launch_error == 13 || launch_error == 127)
			error_processor(command, argv[0], input, launch_error);
		free_command(command);
		if (input)
			free(input), input = NULL;
		fflush(stdout);
	}
	return (0);
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
				input[iter] == '\n' ||
				input[iter] == '\t' ||
				input[iter] == '\r'
			)
				spaces++;
	return (spaces == _strlen(input) ? 1 : 0);
}

/**
 * parse_input - parses/tokenizes input into string vector
 * @input: object string
 * @command: destination string vector
 * @delim: delimiter to be fed to splitting/tokenizing function
 * Return: 1 if input parsed to command, 0 if not, -1 upon improper input/delim
 */

static int parse_input(char *input, char *command[], char *delim)
{
	int iter = 0;
	char *extract_str = NULL, *inpt_cpy = NULL;

	if (!input || !delim)
		return (-1);
	for (inpt_cpy = input; (extract_str = separator(&inpt_cpy, delim)); iter++)
		command[iter] = extract_str;
	if (extract_str)
		extract_str = NULL;
	if (inpt_cpy)
		free(inpt_cpy), inpt_cpy = NULL;
	return (iter ? 1 : 0);
}
