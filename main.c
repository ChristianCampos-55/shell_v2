#include "shell_header.h"

/**
* free_env - free environment variable
* @en: buffer for external environment
* Return: zilch
*/
void free_env(char **en)
{
	int i = 0;

	for (i = 0; en[i] != NULL; i++)
		free(en[i]);
	free(en[i]);
	free(en);
}

/**
* main - call shell
* @ac: argument counter
* @av: argument list
* @env: parsed environment variable
* Return: zilch
*/
int main(int ac, char **av, char **env)
{
	int status = 0;

	if (ac == 1)
	{
		/*cpy of env*/
		/*en  = cpy_env(env)*/
		status = simple_sh(av, env);
		/*free_env(en)*/
		return (status);
	}
	return (0);
}
