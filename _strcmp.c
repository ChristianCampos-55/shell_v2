#include "shell_header.h"

/**
 **_strcmp - compares two strings
 *@string_1: string 1
 *@string_2: string 2
 *Return: sub of two strings
 */
int _strcmp(char *string_1, char *string_2)
{
	int i = 0;
	int res;

	while (string_1[i] != 0 && string_2[i] != 0)
	{
		res = string_1[i] - string_2[i];
		if (res == 0)
		{
			i++;
		}
		else
		{
			break;
			return (res);
		}
	}
	return (res);
}
