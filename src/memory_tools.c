#include "_sh.h"

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
 * _memcpy - copy n bytes of src to dest
 * @dest: place where n bytes of src to be copied
 * @src: source, n bytes of which copied to dest
 * @n: amount of src to be copied to dest
 * Return: dest
 */

char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int iter = 0;

	if (!n)
		return (NULL);
	for (; iter != n; iter++)
		dest[iter] = src[iter];
	return (dest);
}

/**
 * _realloc - reallocates memory & copies memory to new allocation
 * @memory: pointer to memory for which space to be reallocated
 * @old_size: size of current allocation
 * @new_size: expected size of new memory allocation
 * Return: pointer to allocated memory, NULL upon allocation failure
 */

void *_realloc(void *memory, size_t old_size, size_t new_size)
{
	void *new_mem = NULL;

	if (!memory)
	{
		new_mem = malloc(new_size);
		if (!new_mem)
			return (NULL);
	}
	else
	{
		if (old_size < new_size)
		{
			new_mem = malloc(new_size);
			if (!new_mem)
				return (NULL);
			_memcpy(new_mem, memory, old_size);
			free(memory);
		}
		else
			new_mem = memory;
	}
	return (new_mem);
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
