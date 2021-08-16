#include "shell_header.h"

/**
* redir_output_append - select input to exec
* @head: commands list
* @tok_com: selected command
* @status: process status
* Return: status
*/

int redir_output_append(dlistint_t **head, char ***tok_com, int *status)
{
	int stdout_copy = dup(1), result = 0;

	result = stdout_to_end_file(**tok_com);

	if (result == EXIT_IS_DIR || result == EXIT_NOT_ACCESS)
	{
		*status = 2;
		return (result);
	}
	if ((*head)->buffer_in)
	{
		printf("%s", (*head)->buffer_in);
		fflush(stdout);
	}
	set_normal_stdout(stdout_copy);
	return (0);
}

/**
* redir_output - select input to exec
* @head: commands list
* @tok_com: selected command
* @status: process status
* Return: status
*/

int redir_output(dlistint_t **head, char ***tok_com, int *status)
{
	int stdout_copy = dup(1), result = 0;

	result = stdout_to_file(**tok_com);

	if (result == EXIT_IS_DIR || result == EXIT_NOT_ACCESS)
	{
		*status = 2;
		return (result);
	}
	if ((*head)->buffer_in)
	{
		printf("%s", (*head)->buffer_in);
		fflush(stdout);
	}
	set_normal_stdout(stdout_copy);
	return (0);
}

/**
* exe_one_command - select input to exec
* @tokens: input
* @cc: counter
* @en: list of environment variables
* @av: list of user args
* @status: prev stat
* @head: list of all commands
* @tok_com: selected command
* @copy_head: current node command
* Return: status
*/

int or_condition(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head)
{
	int flag_terminator = 0;

	if (copy_head->prev->status)
		createandexesh(tokens, cc, en, av, status, head, tok_com,
			copy_head);
	else
		flag_terminator = 1;
	return (flag_terminator);
}

/**
* exe_one_command - select input to exec
* @tokens: input
* @cc: counter
* @en: list of environment variables
* @av: list of user args
* @status: prev stat
* @head: list of all commands
* @tok_com: selected command
* @copy_head: current node command
* Return: status
*/

int and_condition(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head)
{
	int flag_terminator = 0;

	if (!copy_head->prev->status)
		createandexesh(tokens, cc, en, av, status, head, tok_com,
			copy_head);
	else
		flag_terminator = 1;
	return (flag_terminator);
}

/**
* exe_one_command - select input to exec
* @tokens: input
* @cc: counter
* @en: list of environment variables
* @av: list of user args
* @status: prev stat
* @head: list of all commands
* @tok_com: selected command
* @copy_head: current node command
* Return: status
*/

int exe_multi_commands(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head)
{
	createandexesh(tokens, cc, en, av, status, head, tok_com, copy_head);
	return (0);
}
