#include "shell_header.h"

/**
* env - fill memory
* @tk: value to print
* @env: environment variable
* @buff: reader
* @stat: status of prev loop
* Return: zilch
*/

int env(char **env, char ***tk, char **buff, int *stat)
{
	int i, j;

	(void)tk;
	(void)buff;
	(void)stat;
	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; env[i][j] != '\0'; j++)
			continue;
		write(STDOUT_FILENO, env[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (1);
}

/**
 * _atoi - converts string to integer
 * @s: string to convert
 * Return: converted string
 */
int _atoi(char *s)
{
	int negative = 1, i = 0;
	unsigned int numero = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			negative *= -1;

		else if (s[i] >= 0 + '0' && s[i] < 10 + '0')
			numero = numero * 10 + (s[i] - '0');

		else if (s[i - 1] >= 0 + '0' && s[i - 1] < 10 + '0')
			break;
	}

	return (numero * negative);
}

/**
* exer - fills memory
* @tk: value to print
* @env: environment variable
* @buff: reader
* @stat: status of prev loop
* Return: zilch
*/

int exer(char **env, char ***tk, char **buff, int *stat)
{
	int s = *stat;

	(void)env;
	if ((*tk)[1])
		s = _atoi((*tk)[1]);
	free_all(buff, tk);
	exit(s);
}

/**
* cd - changes current working dir
* @tk: value to print
* @env: environment variable
* @buff: reader
* @stat: status of prev loop
* Return: zilch
*/

int cd(char **env, char ***tk, char **buff, int *stat)
{
	int ret = 0;
	char *home_env = NULL, *prewd = NULL;

	(void)buff;
	(void)stat;
	home_env = _getenv("HOME", env);
	prewd = _getenv("PWD", env);
	if (!(*tk)[1])
		ret = chdir(home_env);
	else
		ret = chdir(prewd);
	return (!ret);
}

/**
* built_ins_sh - fills memory with a constant byte
* @tk: value to print
* @en: environment variable
* @buff: reader
* @stat: status of prev loop
* Return: numbers of characters printed
*/

int built_ins_sh(char ***tk, char **en, char **buff, int *stat)
{
	int j;
	tank o[] = {
		{"env", env},
		{"exit", exer},
		{"cd", cd},
		{NULL, NULL},
	};

	for (j = 0; o[j].op != NULL; j++)
		if (_strcmp((*tk)[0], o[j].op) == 0)
			return (o[j].f(en, tk, buff, stat));
	return (0);
}
