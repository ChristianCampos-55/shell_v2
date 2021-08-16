#include "shell_header.h"

/**
* print_error_builtin - prints error
* @av: parameter called
* @cc: counter
* @token: user input
* @errmsg: error message selector
* Return: zilch
*/

void print_error_builtin(char *av, int cc, char **token, char *errmsg)
{
	fprintf(stderr, "%s: %d: %s: %s%s\n", av, cc,
		token[0], errmsg, token[1]);
}
