#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @new_env: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 * @n: num
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int new_env;
	int status;


	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int hsh(info_t *, char **);
void path_cmmd(info_t *);
int builtin_cmd(info_t *strprm);
void _forkfunction(info_t *strprm);
int loophsh(char **);
int _eputchar(char);
void _eputs(char *);
int _iscmmd(info_t *info, char *path);
int _putsfd(char *str, int fd);
int _putfd(char c, int fd);
char *_dupchars(char *strpth, int begin, int end);
char *_findcmmd(info_t *info, char *strpth, char *cmd);
char *_strcpy(char *, char *);
char *_strdup(const char *);
int _putchar(char);
void _puts(char *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
int _strlen(char *);
int _strcmp(char *, char *);
char *begin_with(const char *, const char *);
char *_strcat(char *, char *);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_memset(char *m, char b, unsigned int f);
void *_realloc(void *ptr, unsigned int prev, unsigned int new_bk);
void free_str(char **s);
int free_ptr(void **);
int int_mode(info_t *stradd);
int _delim(char c, char *delim);
int _isalpha(int);
int _atoi(char *);
int _strtoi(char *s);
char *dig_converter(long int num, int base, int flags);
void cmmt_remover(char *mdf);
int dec_printer(int input, int fd);
void error_printer(info_t *strprm, char *err);
int exit_shell(info_t *);
int do_cd(info_t *);
int cd_help(info_t *);
int hist(info_t *);
int _alias(info_t *);
int unset_alias(info_t *parstr, char *str);
ssize_t _getinput(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
ssize_t _buffin(info_t *strprm, char **bff, size_t *length);
void info_init(info_t *);
void info_set(info_t *, char **);
void info_free(info_t *, int);
char **_getenviron(info_t *argstr);
char *_getenv(info_t *, const char *);
int _env(info_t *);
int _setenviron(info_t *);
int _unsetenviron(info_t *);
int pop_environ_list(info_t *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
size_t list_length(const list_t *);
char **str_list(list_t *);
size_t print_list_t(const list_t *);
list_t *node_beginswith(list_t *, char *, char);
ssize_t index_node(list_t *, list_t *);
int chain_delim(info_t *, char *, size_t *);
void chain_checker(info_t *, char *, size_t *, size_t, size_t);
int alias_rep(info_t *);
int vrb_rep(info_t *);
int str_rep(char **, char *);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_str(const list_t *);
int rem_node(list_t **, unsigned int);
void free_list(list_t **);
char *_histfile(info_t *strprm);
int create_append(info_t *strprm);
int readhist(info_t *strprm);
int add_histlist(info_t *strprm, char *buf, int linecount);
int renum_histlist(info_t *strprm);


#endif
