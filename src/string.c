#include "header/_sh.h"

/**
 * *_strcpy - copies src string to dest
 * @dest: destination memory
 * @src: string to copy terminated by \0
 * Return: pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int iter = 0;

	if (!dest || !src)
		return (NULL);
	for (; src[iter]; iter++)
		dest[iter] = src[iter];
	dest[iter] = '\0';
	return (dest);
}

/**
 * _strcmp - compares 2 strings & shows value upon reaching difference
 * @str1: string 1
 * @str2: string 2
 * Return: value of difference
 */

int _strcmp(char *str1, char *str2)
{
	int iter = 0;

	if (!str1 || !str2)
		return (-1);
	while (str1[iter] == str2[iter] && (str1[iter] || str2[iter]))
		iter++;
	iter = (str1[iter] - str2[iter]);
	return (iter);
}

/**
 * _strlen - returns length of input string
 * @str: string to find length
 * Return: number of characters in string
 */

int _strlen(char *str)
{
	int iter = 0;

	if (!str)
		return (-1);
	for (; str[iter]; iter++)
		;
	return (iter);
}

/**
 * _strdup - duplicates string str & returns pointer to the duplicate
 * @str: object string
 * Return: pointer to duplicate of str
 */

char *_strdup(char *str)
{
	char *copy = NULL;
	int iter_1 = 0, iter_2 = 0;

	if (!str)
		return (NULL);
	iter_2 = _strlen(str) + 1;
	copy = malloc(sizeof(char) * iter_2);
	if (!copy)
		return (NULL);
	for (; iter_1 < iter_2; iter_1++)
		copy[iter_1] = str[iter_1];
	return (copy);
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
