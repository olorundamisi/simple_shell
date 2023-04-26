#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stddef.h>

/**
  * struct input_t - A User defined data type for
  * storing input
  * @data: pointer to string
  * @is_eof: integer
  */
typedef struct input_t
{
	char *data;
	int is_eof;
} input_t;

int is_exit(const char *s);
int _strcmp(const char *s1, const char *s2);
char _fgetc(int fd);
int _printf(char *format, ...);
void init_array(char *buff, size_t num);
char *_strndup(const char *s, int n);
char *_strdup(const char *s);
int _strlen(const char *s);
char **split_string(char *argv, const char *delim);
void free_input(input_t *inp);
int non_interractive(char *name, char **paths_array, char *env[]);
char *_getenv(const char *key, char *environ[]);
char *concat(size_t ac, ...);
char *search_path(char *path, char **paths);
int interractive(char *name, char **paths_array, char *env[]);
void toggle_prompt(int *show);
input_t *get_args_inter(void);
input_t *get_args_non_inter(void);

#endif
