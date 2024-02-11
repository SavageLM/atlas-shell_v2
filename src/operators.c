#include "_sh.h"

/**
 * colon_operator - function for handling colon command operator
 * @commands: selected command segment input
 * Return: 0 on success, otherwise returns -1
*/

int colon_operator(c_list *commands)
{
	int launch_error = 0;

	if (!commands)
		return (-1);
	launch_error = launch_manager(commands->command);
	if (launch_error == 13 || launch_error == 127)
		error_processor(commands->command, launch_error);
	return (0);
}

/**
 * single_right_redirect - function for handling single right redirects
 * @commands: selected command segment input
 * Return: 0 on success, otherwise returns -1
*/

int single_right_redirect(c_list *commands)
{
	int fd = 0, launch_error = 0;
	int redir_out = dup(STDOUT_FILENO);

	if (!commands || !commands->next->command[0] || commands->next->command[1])
		return (-1);
	fd = open(commands->next->command[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		launch_error = launch_manager(commands->command);
		if (launch_error == 13 || launch_error == 127)
			error_processor(commands->command, launch_error);
		fflush(stdout);
		close(fd);
		dup2(redir_out, STDOUT_FILENO);
		close(redir_out);
	}
	else
		return (-1);
	return (0);
}

/**
 * double_right_redirect - function for handling double right redirects
 * @commands: selected command segment input
 * Return: 0 on success, otherwise returns -1
*/

int double_right_redirect(c_list *commands)
{
	int fd = 0, launch_error = 0;
	int redir_out = dup(STDOUT_FILENO);

	if (!commands || !commands->next->command[0] || commands->next->command[1])
		return (-1);
	fd = open(commands->next->command[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		launch_error = launch_manager(commands->command);
		if (launch_error == 13 || launch_error == 127)
			error_processor(commands->command, launch_error);
		fflush(stdout);
		close(fd);
		dup2(redir_out, STDOUT_FILENO);
		close(redir_out);
	}
	else
		return (-1);
	return (0);
}

/**
 * single_left_redirect - function for handling single left redirects
 * @commands: selected command segment input
 * Return: 0 on success, otherwise returns -1
*/

int single_left_redirect(c_list *commands)
{
	int fd = 0, launch_error = 0;
	int redir_in = dup(STDIN_FILENO);

	if (!commands || !commands->next->command[0] || commands->next->command[1])
		return (-1);
	fd = open(commands->next->command[0], O_RDONLY, 0644);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		launch_error = launch_manager(commands->command);
		if (launch_error == 13 || launch_error == 127)
			error_processor(commands->command, launch_error);
		close(fd);
		dup2(redir_in, STDIN_FILENO);
		close(redir_in);
	}
	else
		return (-1);
	return (0);
}

/**
 * double_left_redirect - function for handling double left redirects
 * @commands: selected command segment input
 * Return: 0 on success, otherwise returns -1
*/

int double_left_redirect(c_list __attribute__((unused)) *commands)
{
	return (0);
}
