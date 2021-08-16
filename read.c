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
* count_sign_command - add to buffer
* @buff: range of m to store
* @read: input to find
* Return: zilch
*/

int count_sign_command(char **buff, ssize_t *read)
{
	int i = 0, j = 0, sign_commands = 0, flag_deli = 0;
	char *all_f_gene[] = {">>", ">", "<<", "<", "||", "|", ";", "&&", NULL};
	char **all_flags = all_f_gene;

	for (i = 0; i < *read; i++)
	{
		flag_deli = 0;
		for (j = 0; all_f_gene[j]; j++)
		{
			if (!_strcmp(&((*buff)[i]), all_flags[j]) && i - 1 >= 0 &&
				(*buff)[i] != (*buff)[i - 1])
			{
				flag_deli = 1;
				break;
			}
		}
		if (flag_deli)
			sign_commands++;
	}
	return (sign_commands);
}

/**
* copy_in_new_buffer - add to buffer
* @buff: range of m to store
* @read: input to find
* @new_buff: create new space
* Return: zilch
*/

int copy_in_new_buffer(char **buff, ssize_t *read, char **new_buff)
{
	int i = 0, j = 0, flag_deli = 0, add_spaces = 0, num_sign = 0;
	char *all_f_gene[] = {">>", ">", "<<", "<", "||", "|", ";", "&&", NULL};
	char **all_flags = all_f_gene;

	for (i = 0; i < *read; i++)
	{
		flag_deli = 0, num_sign = 0;
		for (j = 0; all_f_gene[j]; j++)
		{
			if (!_strcmp(&((*buff)[i]), all_flags[j]) && i - 1 >= 0 &&
				(*buff)[i] != (*buff)[i - 1])
			{
				flag_deli = 1;
				for (num_sign = 0; all_flags[j][num_sign] != '\0'; num_sign++)
					continue;
				break;
			}
		}
		if (flag_deli)
		{
			(*new_buff)[i + add_spaces] = ' ';
			if (num_sign == 1)
			{
				(*new_buff)[i + add_spaces + 1] = (*buff)[i];
				(*new_buff)[i + add_spaces + 2] = ' ';
			}
			else
			{
				(*new_buff)[i + add_spaces + 1] = (*buff)[i];
				(*new_buff)[i + add_spaces + 2] = (*buff)[i];
				(*new_buff)[i + add_spaces + 3] = ' ', i++;
			}
			add_spaces += 2;
		}
		else
			(*new_buff)[i + add_spaces] = (*buff)[i];
	}
	(*new_buff)[i + add_spaces] = '\0';
	return (add_spaces);
}

/**
* sure_separate_commands - add to buffer
* @buff: range of m to store
* @read: input to find
* Return: zilch
*/

int sure_separate_commands(char **buff, ssize_t *read)
{
	int sign_commands = 0, add_spaces = 0;
	char *new_buff = NULL;

	sign_commands = count_sign_command(buff, read);
	if (!sign_commands)
		return (0);
	new_buff = malloc(sizeof(char) * ((2 * sign_commands) + *read + 1));
	add_spaces = copy_in_new_buffer(buff, read, &new_buff);
	free(*buff);
	*buff = new_buff, *read += add_spaces;
	return (0);
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
