#include "shell_header.h"

/**
* _setenv - sets the environment variable
* @name: var to search
* @value: value of variable
* @overwrite: overwrite parameter
* @en: environment
* Return: 0 or -1 upon failure
*/
int _setenv(const char *name, const char *value, int overwrite, char ***en)
{
	(void)name;
	(void)value;
	(void)overwrite;
	(void)en;

	return (0);
}

/**
* _unsetenv - unsets variable parameter
* @name: parameter to unset
* @en: environment
* Return: 0 or -1 upon failure
*/
int _unsetenv(const char *name, char ***en)
{
	(void)name;
	(void)en;

	return (0);
}
