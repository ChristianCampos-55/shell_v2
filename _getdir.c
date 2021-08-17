#include "shell_header.h"

/**
 * _getpathdir - gets PATH directories
 * @path: PATH
 * @en: environment variable
 * Return: node of head of parsed list
 */

path_node *_getpathdir(char *path, char **en)
{
	char *token;
	path_node *head = NULL;
	path_node *pathNode;

	if (path == NULL)
		return (NULL);

	pathNode = malloc(sizeof(path_node));
	if (pathNode == NULL)
		return (NULL);

	token = strtok(path, ":");
	if (token[0] == '\0')
		pathNode->str = _getenv("PWD", en);
	else
		pathNode->str = token;
	pathNode->next = head;
	head = pathNode;
	while (token != NULL)
	{
		token = strtok(NULL, ":");
		if (token == NULL)
			break;
		pathNode = malloc(sizeof(path_node));
		if (pathNode == NULL)
			return (NULL);
		pathNode->str = token;
		pathNode->next = head;
		head = pathNode;
	}

	return (head);
}

/**
 * _getenv - gets env var information
 * @variable_env: var to get information for
 * @en: parsed env variable
 * Return: var information or NULL
 */

char *_getenv(const char *variable_env, char **en)
{
	int i, j, flag = 1;

	if (en == NULL)
		return (NULL);
	for (i = 0; en[i] != NULL; i++, flag = 1)
	{
		for (j = 0; en[i][j] != '='; j++)
		{
			if (variable_env[j] != en[i][j])
			{
				flag = 0;
				break;
			}
		}
		if (flag != 0)
			return (&(en[i][j + 1]));
	}
	return (NULL);
}

/**
 * get_path - gets command path
 * @list_path: linked list of directories
 * @en: pointer to environment variable
 * Return: zilch
 */

void get_path(path_node **list_path, char **en)
{
	char *variable_env =  NULL, *copyvari;
	int i;

	variable_env = _getenv("PATH=", en);
	if (variable_env == NULL || variable_env[0] == '\0')
	{
		*list_path = NULL;
		return;
	}
	for (i = 0; variable_env[i] != '\0'; i++)
		;
	copyvari = malloc(sizeof(char) * (i + 1));
	for (i = 0; variable_env[i] != '\0'; i++)
		copyvari[i] = variable_env[i];
	copyvari[i] = '\0';

	*list_path = _getpathdir(copyvari, en);
}
