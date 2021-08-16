#include "shell_header.h"

/**
 **_strcmp - compares two strings
 *@s1: string 1
 *@s2: string 2
 *Return: sub of two strings
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;
	int res;

	while (s1[i] != 0 && s2[i] != 0)
	{
		res = s1[i] - s2[i];
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

/**
 **_strcmp_c - compares two strings
 *@s1: string to compare
 *@s2: string to compare to
 *
 *Return: sub tween both strings
 */

int _strcmp_c(char *s1, char *s2)
{
	int i = 0;
	int res;

	while (s1[i] && s2[i])
	{
		res = s1[i] - s2[i];
		if (res == 0)
			i++;
		else
			return (res);
	}
	res = s1[i] - s2[i];
	return (res);
}

/**
 **_strcmp_n - compares two strings
 *@s1: string to compare
 *@s2: string to compare to
 *@n: int used as counter
 *Return: sub tween both strings
 */

int _strcmp_n(char *s1, char *s2, int n)
{
	int i = 0;
	int res;

	while (s1[i] && s2[i] && i < n)
	{
		res = s1[i] - s2[i];
		if (res == 0)
			i++;
		else
			return (res);
	}
	if (res == 0 && s1[i] == '\0' && s2[i] == '\0')
		res = 0;
	else if (res == 0 && s1[i] == '\n' && s2[i] == '\0')
		res = 0;
	else if (res == 0 && s1[i] == '\0' && s2[i] == '\n')
		res = 0;
	else
		res = s1[i] - s2[i];
	return (res);
}

/**
 **_strcpy - make a copy of passed string
 *@s1: string to copy
 *
 *Return: copy
 */

char *_strcpy(char *s1)
{
	int i = 0, len_s1 = 0;
	char *new_s = NULL;

	for (len_s1 = 0; s1[len_s1]; len_s1++)
		continue;
	new_s = malloc(sizeof(char) * (len_s1 + 1));
	if (!new_s)
		return (NULL);
	for (i = 0; s1[i]; i++)
		new_s[i] = s1[i];
	new_s[i] = '\0';
	return (new_s);
}
