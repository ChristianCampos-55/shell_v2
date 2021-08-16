#include "shell_header.h"

/**
 * _atoi - converts string to integer
 * @s: string to convert
 * @is_number: int to store number convertion
 * Return: converted string
 */
int _atoi(char *s, int *is_number)
{
	int negative = 1, i = 0;
	unsigned int numero = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			negative *= -1;
		else if (s[i] > 57 || s[i] < 48)
		{
			*is_number = 1;
			return (0);
		}
		else if (s[i] >= 0 + '0' && s[i] < 10 + '0')
			numero = numero * 10 + (s[i] - '0');
		else if (s[i - 1] >= 0 + '0' && s[i - 1] < 10 + '0')
			break;
	}
	return (numero * negative);
}

/**
* exi - fills memory
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* @cc: is the counter of commans executes by user
* @av: list containing the arguments given by user
* @head: all commands in a line
* @tok_com: ONE command of a line
* @cur_node: current node command
* Return: zilch
*/

int exi(char ***en, char ***tokens, char **buffer, int *statuss, char **av,
		int *cc, dlistint_t **head, char ***tok_com, dlistint_t *cur_node)
{
	int s = *statuss, is_number = 0;
	char err_message[] = "Illegal number: ";

	(void)av, (void)cc;
	if ((*tok_com)[1])
	{
		s = _atoi((*tok_com)[1], &is_number);
		if (s < 0 || is_number == 1)
		{
			print_error_builtin(*av, *cc, *tok_com, err_message);
			*statuss = 2, cur_node->status = 2;
			return (1);
		}
	}
	free_all(buffer, tokens, head);
	freeenv(*en);
	exit(s);
}

/**
* print_error_cd - prints error of cd
* @av: param inputed
* @cc: counter
* @tokens: user input
* Return: zilch
*/
int print_error_cd(char *av, int cc, char **tokens)
{
	char errmsg[] = "can't cd to ";

	print_error_builtin(av, cc, tokens, errmsg);
	return (1);
}


/**
* cd - changes current working dir
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* @cc: is the counter of commans executes by user
* @av: list containing the arguments given by user
* @head: all commands in a line
* @tok_com: ONE command of a line
* @cur_node: current node command
* Return: zilch
*/

int cd(char ***en, char ***tokens, char **buffer, int *statuss, char **av,
	   int *cc, dlistint_t **head, char ***tok_com, dlistint_t *cur_node)
{
	char  *s1[3] = {NULL, "OLDPWD"}, *s2[3] = {NULL, "PWD"}, *home_env = NULL;
	char  *prewd = _getenv("OLDPWD", *en), **so = s1, **sn = s2;
	int ret = 0;

	(void)buffer, (void)av, (void)cc, (void)ret, (void)cur_node;
	home_env = _getenv("HOME", *en), so[2] = _getenv("PWD", *en);
	if (!prewd)
	{
		_setenv(en, tokens, buffer, statuss, av, cc, head, &so, cur_node);
		prewd = _getenv("OLDPWD", *en);
	}
	if (!(*tok_com)[1])
	{
		if (!home_env)
			return (1);
		ret = chdir(home_env), sn[2] = home_env;
	}
	else
	{
		if (!_strcmp((*tok_com)[1], "-"))
		{
			ret = chdir(prewd);
			if (ret == -1)
				return (print_error_cd(*av, *cc, *tok_com));
			printf("%s\n", prewd), sn[2] = _strcpy(prewd);
			_setenv(en, tokens, buffer, statuss, av, cc, head, &so, cur_node);
			_setenv(en, tokens, buffer, statuss, av, cc, head, &sn, cur_node);
			free(sn[2]);
			return (1);
		}
		else
		{
			ret = chdir((*tok_com)[1]), sn[2] = (*tok_com)[1];
			if (ret == -1)
				return (print_error_cd(*av, *cc, *tok_com));
		}
	}
	_setenv(en, tokens, buffer, statuss, av, cc, head, &so, cur_node);
	_setenv(en, tokens, buffer, statuss, av, cc, head, &sn, cur_node);
	return (1);
}

/**
* built_ins_sh - fills memory with a constant byte
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* @cc: is the counter of commans executes by user
* @av: list containing the arguments given by user
* @head: all commands in a line
* @tok_com: ONE command of a line
* @cur_node: current node command
* Return: number of characters printed
*/

int built_ins_sh(char ***tokens, char ***en, char **buffer, int *statuss,
				 char **av, int *cc, dlistint_t **head, char ***tok_com,
				 dlistint_t *cur_node)
{
	int j;
	op_t o[] = {
		{"env", env},
		{"exit", exi},
		{"cd", cd},
		{"unsetenv", _unsetenv},
		{"setenv", _setenv},
		{NULL, NULL},
	};

	for (j = 0; o[j].op != NULL; j++)
		if (_strcmp((*tok_com)[0], o[j].op) == 0)
			return (o[j].f(en, tokens, buffer, statuss, av, cc,
						   head, tok_com, cur_node));
	return (0);
}
