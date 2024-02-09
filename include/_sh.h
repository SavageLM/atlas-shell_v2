#ifndef __SH_H_
#define __SH_H_

#define SPC_DELIM " \t\n\r"
#define PATH_DELIM ":"
#define MAX_LEN 1024

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * struct program_data - stores data related to program runtime
 * @env_list: adjustable copy of environ
 * @env_list_size: size of memory allocated for env_list
 * @env_size: size of environ upon launch
*/

typedef struct program_data
{
	char **env_list;
	size_t env_list_size;
	size_t env_size;
} p_dt;

extern char **environ;
extern p_dt data;

/* _getenv.c */
char *_getenv(char *var_name);

/* builtin.c */
int builtin(char *input, char **command, char *program);

/* error.c */
void error_processor(char **cmd, char *program, char *input, int code);

/* free */
void free_command(char **command);

/* launch_manager.c */
int launch_manager(char *input, char **command, char *program);

/* memory_tools.c */
void *_calloc(size_t num, size_t size);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *memory, size_t old_size, size_t new_size);
char *_strdup(char *str);
char *str_concat(char *dest, char *src);

/* separator.c */
char *separator(char **input, char *delim);
char *_strsep(char **str, const char *delim);
size_t _strcspn(const char *str1, const char *str2);

/* string.c */
char *_strcat(char *dest, char *src);
int _strcmp(char *str1, char *str2);
int _strncmp(char *str1, char *str2, int limit);
char *_strcpy(char *dest, char *src);
int _strlen(char *str);

/* tools.c */
int _atoi(char *input_string);
int _isdigit(int chr);

int __attribute__ ((constructor)) env_load(void);
void __attribute__ ((destructor)) env_free(void);

#endif
