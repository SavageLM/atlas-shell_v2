#include "_sh.h"

/**
 * _atoi - converts string to integer
 * @input_string: input string to be converted
 * Return: integer form of input string
 */

int _atoi(char *input_string)
{
	int iter = 0, sign = 1, done = 0;
	size_t out = 0;

	for (; input_string[iter] != '\0'; iter++)
	{
		if (input_string[iter] == '-')
			sign = -(sign);
		for (; input_string[iter] >= '0' && input_string[iter] <= '9'; iter++)
			out = (out * 10) + (input_string[iter] - '0'), done = 1;
		if (done)
			break;
	}
	return (out * sign);
}

/**
 * _isdigit - checks if character is a digit
 * @chr: input char checked for digitness
 * Return: 1 if digit, else 0
 */

int _isdigit(int chr)
{
	return (chr >= '0' && chr <= '9' ? 1 : 0);
}
