#ifndef __SH_H_
#define __SH_H_

#define OPS ";&|><"
#define SPC_DELIM " \t\n\r"
#define PATH_DELIM ":"
#define MAX_LEN 1024
#define MAX_WRITE (1024 * 1024 * 2)

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
 * @program: retains program name (argv[0])
 * @env_list: adjustable copy of environ
 * @env_list_size: size of memory allocated for env_list
 * @env_size: size of environ upon launch
*/

typedef struct program_data
{
	char *program;
	char **env_list;
	size_t env_list_size;
	size_t env_size;
} p_dt;

/**
 * struct command_list - node for storing command information, useful when
 *                       controls or redirects used in command input
 * @cmd_str: raw unprocessed string representing single command
 * @command: single processed command vector
 * @cmd_index: stores position in sequence of entered commands, starts at 1
 * @next: pointer to next element in list
 * @prev: pointer to previous element in list
*/

typedef struct command_list
{
	char *cmd_str;
	char *command[MAX_LEN];
	int cmd_index;
	struct command_list *next;
	struct command_list *prev;
} c_list;

/**
 * struct command_data - data bank for each command entered
 * @input: raw unprocessed command line input ending with line break
 * @cmd_count: total number of commands detected in parsed input
 * @op_count: total number of supported control/redirect operators detected
 * @op_array: sequence of detected control/redirect operators
 * @op_add: count to verify op added at each position
 * @op_index: index to keep track of which operators have already been done
 * @commands: doubly-linked list containing commands in sequence as entered
*/

typedef struct command_data
{
	char *input;
	int cmd_count;
	int op_count;
	int op_array[16];
	int op_add;
	int op_index;
	struct command_list *commands;
} c_dt;

extern char **environ;
extern p_dt prog;
extern c_dt cmd_dt;

/* _getenv.c */
char *_getenv(char *var_name);

/* builtin.c */
int builtin(char **command);

/* error.c */
void error_processor(char **cmd, int code);

/* free.c */
void free_cmd_dt(void);
void free_strv(char **command);

/* launcher.c */
int launcher(c_list *commands);
int launch_manager(char **cmd);

/* memory_tools.c */
void *_calloc(size_t num, size_t size);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *memory, size_t old_size, size_t new_size);
char *_strdup(char *str);
char *str_concat(char *dest, char *src);

/* operators.c */
int colon_operator(c_list *commands);
int single_right_redirect(c_list *commands);
int double_right_redirect(c_list *commands);
int single_left_redirect(c_list *commands);
int double_left_redirect(c_list *commands);

/* parse.c */
int parser(char *input);

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
