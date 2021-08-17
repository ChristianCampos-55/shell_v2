#include "shell_header.h"

/**
* add_dnodeint_end - add node to linked list
* @head: header of said list
* Return: address of new node
*/

dlistint_t *add_dnodeint_end(dlistint_t **head)
{
	dlistint_t *new, *headcopy;

	headcopy = *head;

	if (head == NULL)
		return (NULL);

	new = malloc(sizeof(dlistint_t));
	if (new == NULL)
		return (NULL);

	new->buffer_in = NULL;
	new->next_deli = NULL;
	new->tokens = NULL;
	new->status = 0;

	if (*head == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		*head = new;
	}
	else
	{
		while (headcopy->next != NULL)
			headcopy = headcopy->next;
		new->next = NULL;
		new->prev = headcopy;
		headcopy->next = new;
	}

	return (new);
}

/**
* free_dlistint - free list
* @head: header of said list
* Return: address of new node
*/

void free_dlistint(dlistint_t *head)
{
	dlistint_t *savepoin;

	if (head != NULL)
	{
		while (head->prev != NULL)
			head = head->prev;

		while (head != NULL)
		{
			savepoin = head->next;
			if (head->tokens)
				free(head->tokens);
			if (head->buffer_in)
				free(head->buffer_in);
			free(head);
			head = savepoin;
		}
	}
}

/**
* realloc_tokens - argument adder
* @tokens: input
* @word: string to add to command
* Return: adress of alloc or NULL
*/

char **realloc_tokens(char **tokens, char *word)
{
	int index = 0;
	char **new_tokens = NULL;

	if (!tokens)
	{
		new_tokens = malloc(sizeof(char *) * 2);
		if (!new_tokens)
			return (NULL);
		new_tokens[0] = word;
		new_tokens[1] = NULL;
		return (new_tokens);
	}
	for (index = 0; tokens[index]; index++)
		continue;
	new_tokens = malloc(sizeof(char *) * (index + 2));
	if (!new_tokens)
		return (NULL);
	for (index = 0; tokens[index]; index++)
		new_tokens[index] = tokens[index];
	new_tokens[index] = word;
	new_tokens[index + 1] = NULL;
	free(tokens);

	return (new_tokens);
}

/**
* save_mul_commands - save in linked list
* @head: header of said list
* @tokens: input
* @status: error checker
* Return: 1 or 0 upon failure
*/

int save_mul_commands(dlistint_t **head, char ***tokens, int *status)
{
	int i = 0, j = 0, flag_deli = 0;
	dlistint_t *new_node = NULL;
	char *all_f_gene[] = {">", ">>", "<", "<<", "|", ";", "&&", "||", NULL};
	char **all_flags = all_f_gene;

	new_node = add_dnodeint_end(head);
	for (i = 0; (*tokens)[i] != NULL; i++)
	{
		flag_deli = 0;
		for (j = 0; all_flags[j] != NULL; j++)
		{
			if (!_strcmp((*tokens)[i], all_flags[j]))
			{
				flag_deli = 1;
				break;
			}
		}
		if (flag_deli)
			new_node->next_deli = (*tokens)[i];
		else
		{
			new_node->tokens = realloc_tokens(new_node->tokens,
				(*tokens)[i]);
			if (!new_node->tokens)
			{
				*status = 1;
				return (1);
			}
		}
		if ((*tokens)[i + 1] != NULL && flag_deli)
			new_node = add_dnodeint_end(head);
	}
	return (0);
}

/**
* stdin_to_file - open a file to read
* @filename: name of file
* Return: status
*/

int stdin_to_file(char *filename)
{
	int fd = 0;

	fd = open(filename, O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (errno + 1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
