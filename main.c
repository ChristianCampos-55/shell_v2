#include "shell_header.h"

/**
* main - Call shell
* @ac: counter
* @av: argument list
* @env: parsed variable
* Return: zilch
*/

int main(int ac, char **av, char **env)
{
	int status = 0;
	char **en = NULL;

	if (ac == 1)
	{
		en = envdup(env);
		status = simple_sh(av, &en);
		freeenv(en);
		return (status);
	}
	return (0);
}
