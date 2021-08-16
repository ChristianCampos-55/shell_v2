#include "shell_header.h"

/**
* set_all - set par to 0
* @buffer: data storage
* @tokens: tokenizer of user input
* @stat: execution state
* Return: zilch
*/
void set_all(char **buffer, char ***tokens, int *stat)
{
	*stat = 0;
	*buffer = NULL;
	*tokens = NULL;
}

/**
* free_all - free allocations
* @buffer: data storage
* @tokens: tokenizer of user input
* Return: zilch
*/
void free_all(char **buffer, char ***tokens)
{
	free(*buffer);
	free(*tokens);
}

/**
* free_list- frees alocation list
* @list_path: list to free
* Return: zilch
*/
void free_list(p_n *list_path)
{
	p_n *savepoin;

	if (list_path != NULL)
	{
		while (list_path != NULL)
		{
			savepoin = list_path->next;
			if (savepoin == NULL)
				free(list_path->str);
			free(list_path);
			list_path = savepoin;
		}
	}
}
/**
* ctrlc- skip signal
* @ctr_c: signal to skip
* Return: zilch
*/
void ctrlc(int ctr_c __attribute__((unused)))
{
	write(1, "\n($)", 5);
}
/**
* simple_sh - execute shell
* @av: argument list
* @en: environment variable
* Return: zilch
*/
int simple_sh(char **av, char **en)
{
	char *buffer, **tokens;
	int len = 0, status = 0, stat = 0, cont_com = 0;

	signal(SIGINT, ctrlc);
	do {
		cont_com++;
		set_all(&buffer, &tokens, &stat);
		if (isatty(STDIN_FILENO))
			write(1, "($)", 4);
		stat = readsh(&buffer, &len);
		if (stat == 1 || stat == 2)
			free(buffer);
		if (stat == 1)
			continue;
		if (stat == 2)
			return (status);
		parsesh(&buffer, &len, &tokens, &status);
		status = createandexesh(&tokens, &cont_com, en, av, &status);
		free_all(&buffer, &tokens);
	} while (1);
	return (0);
}
