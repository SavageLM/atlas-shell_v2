##**Project**'Shell v2'

## Introduction
> This README is for the C - Shell v2 project at Atlas.
> This document contains all requirements and allowed pre-built functions, as well as steps to compile and run the program.

### Requirements
- Allowed editors: vi, vim, emacs
- All your files will be compiled on Ubuntu 14.04 LTS
- Your C programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic
- A README.md file, at the root of the folder of the project, is mandatory
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- All your header files should be include guarded
- No more than 5 functions per file
- Valgrind should show 0 memory leak and 0 error

### Allowed Function and System Calls
- access
- chdir
- close
- execve
- fork
- stat (__xstat)
- lstat (__lxstat)
- fstat (__fxstat)
- kill
- open
- read
- signal
- wait
- waitpid
- wait3
- wait4
- write
- _exit
- dup
- dup2
- pipe
- unlink
- time
- gethostname
- geteuid
- sigaction
- sigemptyset
- select
- getpid
- _errno_location (ernno macro)
- closedir
- exit
- free
- getcwd
- getline
- malloc
- opendir
- perror
- readdir
- strtok
- localtime
- getpwuid
- isatty
- printf
- fflush
- fprintf
- vfprintf
- sprintf

### Compilation
> This repo contains a makefile for compiling the program using gcc 4.8.4.
> use the command "make all" to build the program.
> the executable file will be "hsh". You can use "./hsh" to lauch the simple shell

### Repo Files
| **File** | *__Description__* |
|----------|----------------:|
|include/_sh.h| Header file for the program, includes all data structs, macros, and prototypes|
|src/_sh.c| Main entry for the program, contains functions for handling the input as well as displaying the prompt and setting/unsetting env|
|src/_getenv.c| File containing function for retrieving the environment|
|src/builtin.c| File containing all functions needed for managing builtins|
|src/error.c| File containing all functions needed for handling errors|
|src/free.c| File containing functions for freeing allocated memory|
|src/launcher.c| File containing all functions for routing input commands and operators, as well as forking applications|
|src/memory_tools.c| File containing all functions for allocating and managing memory|
|src/operations.c| File containing all functions needed for managing operators|
|src/parse.c| File containing all functions for parsing inputs for operators and spaces|
|src/separator.c| File containing all functions for seperating input into seperate commands|
|src/string.c| File containing all functions for manipulating strings|
|src/tools.c| File containing functions for checking if a char is a digit, and for converting strings to digits|
|Makefile| File containing all the rules needed for compiling the program|
|Authors| FIle containing the Authors|