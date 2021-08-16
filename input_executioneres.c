#include "shell_header.h"

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

int out_redir_in(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head)
{
	int flag_terminator = 0, stdout_copy = dup(1), stdin_copy = dup(0);
	int pipefd[2];

	if (!copy_head->prev->status)
	{
		create_pipe(&pipefd);
		stdout_to_stdin(pipefd);
		if ((copy_head->prev)->buffer_in)
		{
			printf("%s", (copy_head->prev)->buffer_in);
			fflush(stdout);
		}
		close(pipefd[1]);
		set_normal_stdout(stdout_copy);
		createandexesh(tokens, cc, en, av, status, head, tok_com,
			copy_head);
		close(pipefd[0]);
		set_normal_stdin(stdin_copy);
	}
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

int redir_input(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head)
{
	int stdin_copy = dup(0), flag_terminator = 0, no_file = 0;

	no_file = stdin_to_file(**tok_com);
	if (no_file)
	{
		print_error(av[0], *cc, (*tok_com)[0], no_file);
	}
	else if (!no_file)
	{
		createandexesh(tokens, cc, en, av, status, head,
			&(copy_head->prev->tokens), copy_head->prev);
		set_normal_stdin(stdin_copy);
		if (copy_head->prev->buffer_in)
		{
			printf("%s", copy_head->prev->buffer_in);
			fflush(stdout);
		}
	}
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

int redir_input_heredoc(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head)
{
	size_t sizebuf = 0;
	ssize_t read = 0;
	char *buff = NULL, *new_input = NULL;
	int stdout_copy = dup(1), stdin_copy = dup(0), pipefd[2], len_tok_com = 0;

	len_tok_com = _strlen(**tok_com);
	do {
		if (isatty(STDIN_FILENO))
			printf("> ");
		read = getline(&buff, &sizebuf, stdin);
		if (!_strcmp_n(buff, **tok_com, len_tok_com))
			break;
		realloc_buffer(&new_input, buff);
		if (read == -1 || buff[read - 1] != '\n')
			break;
		free(buff);
		buff = NULL;
	} while (1);
	free(buff);
	create_pipe(&pipefd);
	stdout_to_stdin(pipefd);
	if (new_input)
	{
		printf("%s", new_input);
		fflush(stdout);
	}
	close(pipefd[1]);
	set_normal_stdout(stdout_copy);
	free(new_input);
	createandexesh(tokens, cc, en, av, status, head,
		&(copy_head->prev->tokens), copy_head->prev);
	close(pipefd[0]);
	set_normal_stdin(stdin_copy);
	if (copy_head->prev->buffer_in)
	{
		printf("%s", copy_head->prev->buffer_in);
		fflush(stdout);
	}
	return (0);
}
