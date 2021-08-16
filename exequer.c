#include "shell_header.h"

/**
* free_tok - frees tokenizer
* @command: parsed input line
* Return: zilch
*/
void free_tok(char *command)
{
	free(command);
}

/**
* _itoa - converts int to string
* @num: int to convert
* @strnum: store for conversion
* Return: converted string
*/
char *_itoa(int num, char *strnum)
{
	int copy_num = num, i, j, div = 1;

	for (i = 0; copy_num != 0; i++)
		copy_num /= 10;
	j = i;
	while (i != 0)
	{
		div *= 10;
		i--;
	}
	div /= 10;
	for (i = 0; i < j; i++)
	{
		strnum[i] = (num / div) + '0';
		num %= div;
		div /= 10;
	}
	strnum[i] = '\0';
	return (strnum);
}

/**
* print_error - error printer (pitb)
* @av: first called param
* @cc: counter
* @tok: user input
* @errmsg: error parser
* Return: zilch
*/
void print_error(char *av, int cc, char *tok, int errmsg)
{
	char strnum[11];
	char *msge = NULL, *cc_str;
	int av_len = 0, tok_len = 0, msg_len = 0, cc_len = 0;

	cc_str = _itoa(cc, strnum);
	cc_len = _strlen(cc_str);
	av_len = _strlen(av);
	tok_len = _strlen(tok);
	if (errmsg == 1)
	{
		msg_len = (16 + av_len + tok_len + cc_len);
		msge = malloc(sizeof(char) * (msg_len + 1));
		msge[0] = '\0';
		_strcat(msge, av);
		_strcat(msge, ": ");
		_strcat(msge, cc_str);
		_strcat(msge, ": ");
		_strcat(msge, tok);
		_strcat(msge, ": ");
		_strcat(msge, "not found\n");
		write(STDERR_FILENO, msge, msg_len);
	}
	if (errmsg == 0)
	{
		msg_len = (24 + av_len + tok_len + cc_len);
		msge = malloc(sizeof(char) * (msg_len + 1));
		msge[0] = '\0';
		_strcat(msge, av);
		_strcat(msge, ": ");
		_strcat(msge, cc_str);
		_strcat(msge, ": ");
		_strcat(msge, tok);
		_strcat(msge, ": ");
		_strcat(msge, "Permission denied\n");
		write(STDERR_FILENO, msge, msg_len);
	}
	free(msge);
}

/**
* check_command - execute command
* @tokens: user input
* @cc: command counter
* @en: parameters to execve
* @av: user arguments
* @stats: status of previous loop
* Return: stat
*/

int check_command(char ***tokens, int *cc, char **en, char **av, int *stats)
{
	int statu = 0;
	char **buffer = *tokens, *tok = NULL;
	struct stat st;

	st.st_mode = 0;
	statu = built_ins_sh(tokens, en, buffer, stats);
	if (statu != 0)
		return (2);
	statu = add_path(tokens, en);
	if (statu == 127)
	{
		print_error(av[0], *cc, (*tokens)[0], 1);
		return (statu);
	}
	tok = (*tokens)[0];
	stat(tok, &st);
	if ((access(tok, F_OK | X_OK) == 0) &&
		((st.st_mode & S_IFMT) == S_IFREG))
	{
		return (statu);
	}
	else
	{
		if ((st.st_mode & S_IFMT) == S_IFDIR)
		{
			print_error(av[0], *cc, tok, 0);
			return (126);
		}
		if (access(tok, F_OK) != 0)
		{
			print_error(av[0], *cc, tok, 1);
			return (127);
		}
		else if (access(tok, X_OK) != 0)
		{
			print_error(av[0], *cc, tok, 0);
			return (126);
		}
	}
	return (0);
}

/**
* createandexesh - executer
* @tokens: strings from stdin
* @cc: user input
* @en: parameters to execve
* @av: user arguments
* @stats: status of previous loop
* Return: the process status
*/
int createandexesh(char ***tokens, int *cc, char **en, char **av, int *stats)
{
	pid_t child_pid;
	int wait_status = 0, statu = 0, exit_stat = 0;
	char *command = **tokens, *trans;

	statu = check_command(tokens, cc, en, av, stats);
	if (statu != 0 && statu != 1)
	{
		if (statu == 2)
			return (0);
		return (statu);
	}
	trans = (*tokens)[0];
	(*tokens)[0] = command;
	command = trans;
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		if (execve(command, *tokens, en) == -1)
		{
			if (statu == 1)
				free_tok(command);
			exit(50);
		}
	}
	else
	{
		waitpid(child_pid, &wait_status, 0);
		if (WIFEXITED(wait_status))
			exit_stat = WEXITSTATUS(wait_status);
	}
	if (statu == 1)
		free_tok(command);

	return (exit_stat);
}
