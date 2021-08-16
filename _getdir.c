#include "shell_header.h"

/**
 * _getpathdir - gets PATH directories
 * @path: PATH
 * @env: environment variable
 * Return: node of head of parsed list
 */
p_n *_getpathdir(char *path, char **env)
{
	char *token;
	p_n *head = NULL;
	p_n *pathNode;

	if (path == NULL)
		return (NULL);

	pathNode = malloc(sizeof(p_n));
	if (pathNode == NULL)
		return (NULL);

	token = strtok(path, ":");
	if (token[0] == '\0')
		pathNode->str = _getenv("PWD", env);
	else
		pathNode->str = token;
	pathNode->next = head;
	head = pathNode;
	while (token != NULL)
	{
		token = strtok(NULL, ":");
		if (token == NULL)
			break;
		pathNode = malloc(sizeof(p_n));
		if (pathNode == NULL)
			return (NULL);
		pathNode->str = token;
		pathNode->next = head;
		head = pathNode;
	}

	return (head);
}
