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

/**
 * _strcat - concatenates 2 strings
 * @dest: string 1 to have src appended to end
 * @src: string 2 to append to end of dest
 * Return: dest
 */

char *_strcat(char *dest, char *src)
{
	int iter_1 = _strlen(dest), iter_2 = 0;

	if (!dest || !src)
		return (NULL);
	for (; src[iter_2]; iter_1++, iter_2++)
		dest[iter_1] = src[iter_2];
	dest[iter_1] = '\0';
	return (dest);
}

/**
 * str_concat - concatenates two given strings
 * @dest: string to which src is to be concatenated "to"
 * @src: string concatenated to dest "from"
 * Return: pointer to ret_str of concat in resp. freshly allocated memory
 */

char *str_concat(char *dest, char *src)
{
	size_t dest_iter = 0, src_iter = 0, dest_len = 0, src_len = 0;
	char *ret_str = 0;

	if (!dest)
		dest = "";
	if (!src)
		src = "";
	dest_len = _strlen(dest), src_len = _strlen(src) + 1;
	ret_str = malloc(sizeof(char) * (dest_len + src_len));
	if (!ret_str)
		return (NULL);
	for (; dest[dest_iter]; dest_iter++)
		ret_str[dest_iter] = dest[dest_iter];
	for (; src[src_iter]; dest_iter++, src_iter++)
		ret_str[dest_iter] = src[src_iter];
	ret_str[dest_iter] = '\0';
	return (ret_str);
}
