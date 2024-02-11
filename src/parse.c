#include "_sh.h"

static void detect_ops(char *input);
static int parse_ops(char *input);
static int add_cmd(char *extract_str, c_list **commands);
static int parse_space(c_list *cmd);

/**
 * parser - manages parsing work to be performed upon command line input
 * @input: input from command line
 * Return: 0 upon success, -1 upon improper input
*/

int parser(char *input)
{
	c_list *tmp = NULL;
	int ops_parsed = 0, iter = 0;

	if (!input)
		return (-1);
	detect_ops(input);
	ops_parsed = parse_ops(input);
	if (!ops_parsed)
		add_cmd(input, &cmd_dt.commands);
	for (tmp = cmd_dt.commands; tmp; tmp = tmp->next)
		parse_space(tmp);
	return (0);
}

/**
 * detect_ops - detect compatible operators from input & populates op_array as
 *              well as command data counters
 * @input: input from command line
*/

static void detect_ops(char *input)
{
	int iter = 0;

	for (; input[iter]; iter++)
	{
		if (input[iter] == ';')
			cmd_dt.op_array[cmd_dt.op_add++] = 0x1, cmd_dt.op_count++;
		else if (input[iter] == '&' && input[iter + 1] == '&')
			cmd_dt.op_array[cmd_dt.op_add++] = 0x2, cmd_dt.op_count++, iter++;
		else if (input[iter] == '|' && input[iter + 1] != '|')
			cmd_dt.op_array[cmd_dt.op_add++] = 0x3, cmd_dt.op_count++;
		else if (input[iter] == '|' && input[iter + 1] == '|')
			cmd_dt.op_array[cmd_dt.op_add++] = 0x4, cmd_dt.op_count++, iter++;
		else if (input[iter] == '>' && input[iter + 1] != '>')
			cmd_dt.op_array[cmd_dt.op_add++] = 0x5, cmd_dt.op_count++;
		else if (input[iter] == '>' && input[iter + 1] == '>')
			cmd_dt.op_array[cmd_dt.op_add++] = 0x6, cmd_dt.op_count++, iter++;
		else if (input[iter] == '<' && input[iter + 1] != '<')
			cmd_dt.op_array[cmd_dt.op_add++] = 0x7, cmd_dt.op_count++;
		else if (input[iter] == '<' && input[iter + 1] == '<')
			cmd_dt.op_array[cmd_dt.op_add++] = 0x8, cmd_dt.op_count++, iter++;
	}
}

/**
 * parse_ops - .
 * @input: input entered to command line
 * Return: 1 if input parsed, 0 if not, -1 upon improper input
*/

static int parse_ops(char *input)
{
	char *extract_str = NULL, *inpt_cpy = NULL;

	if (!input)
		return (-1);
	for (
		inpt_cpy = input;
		(extract_str = separator(&inpt_cpy, OPS));
		cmd_dt.cmd_count++
	)
		add_cmd(extract_str, &cmd_dt.commands);
	if (extract_str)
		extract_str = NULL;
	if (inpt_cpy)
		free(inpt_cpy), inpt_cpy = NULL;
	return (cmd_dt.cmd_count ? 1 : 0);
}

/**
 * add_cmd - adds node to command segment list
 * @extract_str: split string from command line input containing command string
 * @commands: list of separated command segments
 * Return: 0 upon succes, -1 upon memory allocation failure
*/

static int add_cmd(char *extract_str, c_list **commands)
{
	c_list *add = NULL, *tmp = NULL;

	if (!extract_str)
		return (-1);
	add = _calloc(sizeof(c_list), 1);
	if (!add)
		return (-1);
	add->cmd_str = _strdup(extract_str);
	add->cmd_index = cmd_dt.cmd_count + 1;
	add->next = NULL;
	if (!*commands)
		add->prev = NULL,
		*commands = add;
	else
	{
		for (tmp = *commands; tmp; tmp = tmp->next)
			if (!tmp->next)
			{
				add->prev = tmp;
				tmp->next = add;
				break;
			}
	}
	return (0);
}

/**
 * parse_space - parses/tokenizes input by whitespace into string vector
 * @cmd: command list
 * Return: 1 if input parsed to command, 0 if not, -1 upon improper input
 */

static int parse_space(c_list *cmd)
{
	int iter = 0;
	char *extract_str = NULL, *inpt_cpy = NULL;

	if (!cmd)
		return (-1);
	for (
		inpt_cpy = cmd->cmd_str;
		(extract_str = separator(&inpt_cpy, SPC_DELIM));
		iter++
	)
		cmd->command[iter] = _strdup(extract_str);
	if (extract_str)
		extract_str = NULL;
	if (inpt_cpy)
		free(inpt_cpy), inpt_cpy = NULL;
	return (iter ? 1 : 0);
}
