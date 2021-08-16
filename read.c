#include "shell_header.h"

/**
* num_tokens - tokens to execute
* @buffer: buffer of tokenized user parameters
* @read: parsed env
* Return: nodes
*/

int num_tokens(char **buffer, ssize_t read)
{
	const char delim[] = " \t\n";
	char *token, *copybuffer = NULL;
	int i;

	copybuffer = malloc(sizeof(char) * read + 1);
	if (copybuffer == NULL)
	{
		perror("Error");
		return (0);
	}
	for (i = 0; buffer[0][i] != '\0'; i++)
		copybuffer[i] = buffer[0][i];
	copybuffer[i] = buffer[0][i];
	token = strtok(copybuffer, delim);
	for (i = 0; token != NULL; i++)
		token = strtok(NULL, delim);
	free(copybuffer);
	return (i);
}

/**
* readsh - parser of user input
* @buff: buffer to store user data
* @len: lenght of buffer
* Return: zilch
*/

int readsh(char **buff, int *len)
{
	ssize_t read = 0;
	size_t sizebuf = 0;
	int i;
	char *b = NULL;

	read = getline(buff, &sizebuf, stdin);
	if (read == -1 || (*buff)[read - 1] != '\n')
	{
		if (isatty(STDIN_FILENO))
			write(1, "\n", 1);
		return (2);
	}
	b = buff[0];
	for (i = 0; b[i] == ' ' || b[i] == '\t'; i++)
	{
		if (b[i + 1] == '\n')
			return (1);
	}
	if (b[0] == '\n')
		return (1);
	*len = num_tokens(buff, read);
	return (0);
}
