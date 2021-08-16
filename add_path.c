#include "shell_header.h"

/**
 *_strlen - length of a string
 *@string: string to input
 *Return: the length of string
 */

int _strlen(char *string)
{
	int i = 0;

	for (i = 0; string[i] != '\0'; i++)
		;
	return (i);
}

/**
* _strcat - check for specific string
* @dest: pointer to destination
* @src: pointer to source
* Return: Always 0.
*/

char *_strcat(char *dest, char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
		dest[i + j] = src[j];

	dest[i + j] = '\0';
	return (dest);
}

/**
 *add_path - adds path for command
 *@tk: string tokenized input line
 *@env: environ global variable
 *Return: 0
 */

int add_path(char ***tk, char **env)
{
	char *com_user = NULL, *new_path = NULL;
	int lencom_user, len_dir;
	p_n *list_path, *path_cpy;

	if (tk == NULL)
		return (0);
	if (access((*tk)[0], F_OK | R_OK | X_OK) == 0 &&
		(((*tk)[0])[0] == '/' || ((*tk)[0])[0] == '.'))
	{
		return (0);
	}
	get_path(&list_path, env);
	if (list_path == NULL)
		return (127);
	path_cpy = list_path;
	com_user = *(tk)[0];
	lencom_user = _strlen(com_user);
	while (list_path != NULL)
	{
		len_dir = _strlen(list_path->str);
		new_path = malloc((len_dir + lencom_user + 2) * sizeof(char));
		new_path[0] = '\0';
		_strcat(new_path, list_path->str);
		_strcat(new_path, "/");
		_strcat(new_path, com_user);
		if (access(new_path, F_OK | X_OK) == 0)
		{
			(*tk)[0] = new_path;
			free_list(path_cpy);
			return (1);
		}
		free(new_path);
		new_path = NULL;
		list_path = list_path->next;
	}
	free_list(path_cpy);
	return (0);
}
