#ifndef SHELL_HEADER
#define SHELL_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/**
* struct op_t - struct for operators
*
* @op: operator for function
* @f: associated function
*/
typedef struct op_t
{
	char *op;
	int (*f)(char **, char ***, char **, int *);
} tank;

/**
* struct p_n - linked list
* @str: string - name of a directorie's path
* @next: points to the next node
*
* Description: buffer for all directories
*/

typedef struct p_n
{
	char *str;
	struct p_n *next;
} p_n;

char *_strcat(char *dest, char *src);
int _strlen(char *st);
int simple_sh(char **av, char **en);
int readsh(char **buffer, int *len);
p_n *_getpathdir(char *path, char **);
int add_path(char ***tokens, char **en);
void get_path(p_n **list_path, char **en);
int _strcmp(char *s1, char *s2);
void free_list(p_n *list_path);
void free_all(char **buffer, char ***tokens);
void free_env(char **en);
int _setenv(const char *name, const char *value, int overwrite, char ***ev);
int built_ins_sh(char ***tokens, char **en, char **buffer, int *);
void parsesh(char **buffer, int *len, char ***tokens, int *status);
int _unsetenv(const char *name, char ***ev);
int createandexesh(char ***, int *, char **, char **, int *);
char *_getenv(const char *variable_env, char **en);

#endif
