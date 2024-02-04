#include "header/_sh.h"

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
 * _calloc - allocates memory & initializes memory to 0 for array of objects
 *           of specified size
 * @num: array object count for which memory to be allocated
 * @size: size of each array object
 * Return: pointer to allocated memory, NULL if either param is 0 or alloc fail
 */

void *_calloc(size_t num, size_t size)
{
	void *memory = NULL;
	char *initialize = NULL;
	size_t iter = 0;

	if (!num || !size)
		return (NULL);
	memory = malloc(num * size);
	if (!memory)
		return (NULL);
	for (iter = 0, initialize = memory; iter != (size * num); iter++)
		initialize[iter] = '\0';
	return (memory);
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
