#include "shell_header.h"

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
	const char delim[] = " \t\n";

	(void) status;
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
