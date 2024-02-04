#ifndef __SH_H_
#define __SH_H_

#define SPC_DELIM " \t\n\r"
#define PATH_DELIM ":"
#define MAX_LEN 1024

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

/* _getenv.c */
char *_getenv(char *var_name);

/* builtin.c */
int builtin(char *input, char **command);

/* error.c */
void error_processor(char **cmd, char *program, char *input, int code);

/* free.c */
void free_command(char **command);

/* launch_manager.c */
int launch_manager(char *input, char **command);

/* separator.c */
char *separator(char **input, char *delim);
char *_strsep(char **str, const char *delim);
size_t _strcspn(const char *str1, const char *str2);

/* string.c */
char *_strcpy(char *dest, char *src);
int _strcmp(char *str1, char *str2);
int _strncmp(char *str1, char *str2, int limit);
int _strlen(char *str);
char *_strdup(char *str);

/* tools.c */
int _atoi(char *input_string);
void *_calloc(size_t num, size_t size);
int _isdigit(int chr);
char *_strcat(char *dest, char *src);
char *str_concat(char *dest, char *src);


#endif
