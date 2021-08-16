#include "shell_header.h"

/**
 * _getenv - gets env var information
 * @variable_env: var to get information for
 * @env: parsed env variable
 * Return: var information or NULL
 */
char *_getenv(const char *variable_env, char **env)
{
	int i, j, flag = 1;

	if (env == NULL)
		return (NULL);
	for (i = 0; env[i] != NULL; i++, flag = 1)
	{
		for (j = 0; env[i][j] != '='; j++)
		{
			if (variable_env[j] != env[i][j])
			{
				flag = 0;
				break;
			}
		}
		if (flag != 0)
			return (&(env[i][j + 1]));
	}
	return (NULL);
}
