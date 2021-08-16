#include "shell_header.h"

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
