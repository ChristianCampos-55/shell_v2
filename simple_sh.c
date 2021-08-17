#include "shell_header.h"

/**
* set_all - set par to 0
* @buffer: data storage
* @tokens: tokenizer of user input
* @stat: execution state
* @head: head of list
* Return: zilch
*/

void set_all(char **buffer, char ***tokens, int *stat, dlistint_t **head)
{
	*stat = 0;
	*buffer = NULL;
	*tokens = NULL;
	*head = NULL;
}

/**
* free_all - free allocations
* @buffer: data storage
* @tokens: tokenizer of user input
* @head: head of list
* Return: zilch
*/
void free_all(char **buffer, char ***tokens, dlistint_t **head)
{
	if (*buffer)
		free(*buffer);
	if (*tokens)
		free(*tokens);
	if (*head)
		free_dlistint(*head);
}

/**
* free_list- frees alocation list
* @list_path: list to free
* Return: zilch
*/

void free_list(path_node *list_path)
{
	path_node *savepoin;

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

int simple_sh(char **av, char ***en)
{
	char *buffer, **tokens;
	int len = 0, status = 0, stat = 0, cont_com = 0;
	dlistint_t *head;

	signal(SIGINT, ctrlc);
	do {
		cont_com++;
		set_all(&buffer, &tokens, &stat, &head);
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
		save_mul_commands(&head, &tokens, &status);
		exe_mul_commands(&tokens, &cont_com, en, av, &status, &head);
		free_all(&buffer, &tokens, &head);
	} while (1);
	return (0);
}
