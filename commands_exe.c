#include "shell_header.h"

/**
* create_pipe - genesis
* @pipefd: array of genesis
* Return: status
*/

int create_pipe(int (*pipefd)[2])
{
	if (pipe(*pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
* read_command_output - genesis
* @pipefd: array of genesis
* @cur_node: current node
* Return: status
*/

int read_command_output(int *pipefd, dlistint_t *cur_node)
{
	char buff[1025] = "";
	int i = 0;

	close(pipefd[1]);
	for (i = 0; i < 1025; i++)
		buff[i] = '\0';
	while (read(pipefd[0], &buff, 1024) > 0)
	{
		realloc_buffer(&(cur_node->buffer_in), buff);
		for (i = 0; i < 1025; i++)
			buff[i] = '\0';
	}
	close(pipefd[0]);
	return (0);
}

/**
* change_output_command - genesis
* @pipefd: array of genesis
* Return: status
*/

int change_output_command(int *pipefd)
{
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	close(pipefd[1]);
	return (0);
}

/**
* realloc_buffer - add com to buffer
* @buffer: command upon execution
* @str: new com to add
* Return: status
*/

int realloc_buffer(char **buffer, char *str)
{
	char *new_buffer = NULL;
	int size_buffer = 0, size_str = 0, i = 0;

	if (!str || str[0] == '\0')
		return (0);
	for (size_buffer = 0; *buffer && (*buffer)[size_buffer]; size_buffer++)
		continue;
	for (size_str = 0; str && str[size_str]; size_str++)
		continue;
	new_buffer = malloc(sizeof(char) * (size_str + size_buffer + 1));
	if (!new_buffer)
		return (1);
	for (i = 0; i < size_buffer + size_str; i++)
	{
		if (i < size_buffer)
			new_buffer[i] = (*buffer)[i];
		else
			new_buffer[i] = str[i - size_buffer];
	}
	new_buffer[i] = '\0';
	if (*buffer)
		free(*buffer);
	*buffer = new_buffer;
	return (0);
}
/**
* parsesh - buffer parser
* @buffer: buffer to store data in
* @tokens: tokenized buffer
* @len: tokenizer length
* @status: status of execution
* Return: zilch
*/

void parsesh(char **buffer, int *len, char ***tokens, int *status)
{
	char *token;
	int i;
	const char delim[] = " \t\n\"";

	(void)status;
	*tokens = malloc(sizeof(char *) * (*len + 1));
	if (*tokens == NULL)
	{
		printf("Error\n");
		return;
	}
	token = strtok(*buffer, delim);
	for (i = 0; token != NULL; i++)
	{
		(*tokens)[i] = token;
		token = strtok(NULL, delim);
	}
	(*tokens)[i] = token;
}
