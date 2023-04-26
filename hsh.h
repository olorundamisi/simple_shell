#ifndef _HSH_H_
#define _HSH_H_


/**
 * simple_shell - Contains the following files:
 *	buffer_handling.c
 *	chaining_and_delimiters.c
 *	env.c
 *	env_helper.c
 *	err_handling.c
 *	err_handling_helper.c
 *	hsh_aliasing.c
 *	hsh_builtins.c
 *	hsh.c
 *	hsh.h
 *	hsh_helper.c
 *	hsh_history.c
 *	linked_list.c
 *	linked_list_helper.c
 *	main.c
 *	mem_alloc.c
 *	mem_free.c
 *	parser_and_lexer.c
 *	shell_args.c
 *	str_compute.c
 *	strn_compute.c
 *	str_write.c
 *	variables.c
 */


#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


#ifndef _ERROR_7E_
#define _ERROR_7E_ 126
#endif

#ifndef _ERROR_7F_
#define _ERROR_7F_ 127
#endif

#ifndef _ERROR_NO_ENTITY_
#define _ERROR_NO_ENTITY_ ENOENT
#endif

#ifndef _ERROR_NO_ACCESS_
#define _ERROR_NO_ACCESS_ EACCES
#endif


#ifndef _MEM_ALLOCATE_
#define _MEM_ALLOCATE_ malloc
#endif

#ifndef BUF_FLUSH
#define BUF_FLUSH -1
#endif

#ifndef R_BUF_SIZE
#define R_BUF_SIZE 1024
#endif

#ifndef W_BUF_SIZE
#define W_BUF_SIZE 1024
#endif

#ifndef CMD_NORM
#define CMD_NORM	0
#endif

#ifndef CMD_OR
#define CMD_OR		1
#endif

#ifndef CMD_AND
#define CMD_AND		2
#endif

#ifndef CMD_CHAIN
#define CMD_CHAIN	3
#endif

/* Possibly deprecated... */
#ifndef CMD_PIPE
#define CMD_PIPE	4
#endif

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define _LIB_GETLINE 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096


/**
 * struct list_s - structure for singly linked list
 *
 * @num: integer
 * @str: string (please use _MEM_ALLOCATE_() for stability)
 * @next: point to next node of singly linked list
 *
 * Description: singly linked list node structure
 */

typedef struct list_s
{
	int num;
	char *str;
	struct list_s *next;
} list_t;


extern char **environ;	/* extern char "environ" from low level env */


/**
 * struct shell_info - the `shell_info` structure encapsulates arguments
 *	that will be moved around the functions while `hsh` is running.
 *
 * @argc: integer contaning argc
 * @buffer_type: buffer type of command could be ( ||, &&, ; )
 * @changed_environ: should be `bool` but is int - for if env is changed
 * @exit_err_code: containing error code for `exit()`
 * @hl_count: count for number of history lines
 * @lc_flag: if set to `1` count current input line
 * @r_file_desc: contains line input from `file description`
 * @status: stores the return value of previous command
 * @error_l_cnt: maintains the number of errors
 *
 * @argv: char * of char * containing argv
 * @cmd_buf_addr: char * containing address of pointer to command buffer
 * @environ: char * clone from low-level environment
 * @arg: char * (string) from `getline` and it encapsulates args
 * @filename: char * filename for the program
 * @path: char * path for the present command
 *
 * @alias: linked list alias
 * @env: singly llist_t clone of environ
 * @history: linked list containing history
 */

typedef struct shell_info
{
	int argc;
	int buffer_type;
	int changed_environ;
	int exit_err_code;
	int hl_count;
	int lc_flag;
	int r_file_desc;
	int status;
	unsigned int error_l_cnt;

	char **argv;
	char **cmd_buf_addr;
	char **environ;
	char *arg;
	char *filename;
	char *path;

	list_t *alias;
	list_t *env;
	list_t *history;
} shell_args_t;


/**
 * struct builtin - contains a builtin string and related function
 *
 * @type: the builtin command flag
 * @func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(shell_args_t *);
} builtin_dict;


char **_get_environ(shell_args_t *);
char **lexer(char *, char *);
char **list_to_strings(list_t *);
char *_getenv(shell_args_t *, const char *);
char *_memset(char *, char, unsigned int);
char *_starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strchr(char *, char);
char *_strcpy(char *, char *);
char *_strdup(const char *);
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *change_num_base(long int, int, int);
char *duplicate_chars(char *, int, int);
char *fetch_hist_file(shell_args_t *shell_args);
char *find_path(shell_args_t *, char *, char *);
int _alias_emul(shell_args_t *);
int _cd_emul(shell_args_t *);
int _env_emul(shell_args_t *);
int _error_atoi(char *);
int _error_put_dec(int, int);
int _error_insert_character(char);
int _exit_emul(shell_args_t *);
int _getline(shell_args_t *, char **, size_t *);
int _help_emul(shell_args_t *);
int _history_emul(shell_args_t *);
int _insert_character(char);
int _insert_character_file_desc(char c, int fd);
int _insert_str_file_desc(char *str, int fd);
int _replace_alias(shell_args_t *);
int _setenv(shell_args_t *, char *, char *);
int _setenv_emul(shell_args_t *);
int _strcmp(char *, char *);
int _strlen(char *);
int _unsetenv(shell_args_t *, char *);
int _unsetenv_emul(shell_args_t *);
int append_to_hist(shell_args_t *, char *, int);
int bfree(void **);
int del_node_at_idx(list_t **, unsigned int);
int get_builtin(shell_args_t *);
int hsh_generate_env(shell_args_t *);
int hsh_main(shell_args_t *, char **);
int hsh_r_hist(shell_args_t *shell_args);
int hsh_renum_hist(shell_args_t *shell_args);
int hsh_w_hist(shell_args_t *shell_args);
int is_chain_delimiter(shell_args_t *, char *, size_t *);
int is_delimiter(char, char *);
int is_executable(shell_args_t *, char *);
int replace_string(char **, char *);
int replace_variables(shell_args_t *);
list_t *add_node(list_t **, const char *, int);
list_t *append_node_to_end(list_t **, const char *, int);
list_t *node_sw(list_t *, char *, char);
size_t list_len(const list_t *);
size_t write_llist(const list_t *);
size_t write_llist_str(const list_t *);
ssize_t get_node_idx(list_t *, list_t *);
ssize_t input_buffer(shell_args_t *, char **, size_t *);
ssize_t r_input(shell_args_t *);
void *_realloc(void *, unsigned int, unsigned int);
void _BLOCK_SIGINT(int);
void _error_print_mesg(shell_args_t *, char *);
void _error_insert_str(char *);
void _insert_str(char *);
void assert_cont_chain(shell_args_t *, char *, size_t *, size_t, size_t);
void clear_llist(list_t **);
void clear_shell_args(shell_args_t *);
void ffree(char **);
void find_cmd_in_path(shell_args_t *);
void fork_exec_thread(shell_args_t *);
void free_shell_args(shell_args_t *, int);
void handle_comments(char *);
void hsh_asm_file_desc(int file_desc);
void raise_enoent(char *arg0, char *arg1);
void raise_errors(char *arg0, char *arg1);
void set_shell_args(shell_args_t *, char **);
void start_hsh(shell_args_t *shell_args, char **arg_vec);


#endif /* _HSH_H_ */
