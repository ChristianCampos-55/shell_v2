#include "shell_header.h"

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
