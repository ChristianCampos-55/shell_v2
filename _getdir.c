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
