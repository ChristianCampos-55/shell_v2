#include "shell_header.h"

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
	char *message = NULL, *cc_str;
	int av_len = 0, tok_len = 0, msg_len = 0, cc_len = 0;

	cc_str = _itoa(cc, strnum);
	cc_len = _strlen(cc_str);
	av_len = _strlen(av);
	tok_len = _strlen(tok);
	if (errmsg == 1)
	{
		msg_len = (16 + av_len + tok_len + cc_len);
		message = malloc(sizeof(char) * (msg_len + 1));
		message[0] = '\0';
		_strcat(message, av);
		_strcat(message, ": ");
		_strcat(message, cc_str);
		_strcat(message, ": ");
		_strcat(message, tok);
		_strcat(message, ": ");
		_strcat(message, "not found\n");
		write(STDERR_FILENO, message, msg_len);
	}
	else if (errmsg == 0)
	{
		msg_len = (24 + av_len + tok_len + cc_len);
		message = malloc(sizeof(char) * (msg_len + 1));
		message[0] = '\0';
		_strcat(message, av);
		_strcat(message, ": ");
		_strcat(message, cc_str);
		_strcat(message, ": ");
		_strcat(message, tok);
		_strcat(message, ": ");
		_strcat(message, "Permission denied\n");
		write(STDERR_FILENO, message, msg_len);
	}
	else
		open_errors(av, cc, tok, errmsg);
	free(message);
}

/**
* check_command - execute command
* @tokens: user input
* @cc: command counter
* @en: parameters to execve
* @av: user arguments
* @statuss: status of previous loop
* @head: all commands in a line
* @tok_com: ONE command of a line
* @cur_node: current node command
* Return: stat
*/

int check_command(char ***tokens, int *cc, char ***en, char **av,
				  int *statuss, dlistint_t **head, char ***tok_com, dlistint_t *cur_node)
{
	int statu = 0;
	char **buffer = *tokens, *tok = NULL;
	struct stat st = {0};

	statu = built_ins_sh(tokens, en, buffer, statuss, av, cc, head, tok_com,
						 cur_node);
	if (statu != 0)
		return (2);
	statu = add_path(tok_com, *en);
	if (statu == 127)
	{
		print_error(av[0], *cc, (*tok_com)[0], 1);
		return (statu);
	}
	tok = (*tok_com)[0];
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
* exe_command - executer
* @en: parameters to execve
* @statuss: status of previous loop
* @statu: pointer to current loop
* @tok_com: ONE command of a line
* @cur_node: current node command
* @command: input received by user
* Return: the process status
*/

int exe_command(int statu, char ***en, int *statuss, char ***tok_com,
				dlistint_t *cur_node, char *command)
{
	int wait_status = 0, exit_stat = 0, pipefd[2];
	pid_t child_pid;

	create_pipe(&pipefd);
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		*statuss = 1;
		return (1);
	}
	if (child_pid == 0)
	{
		change_output_command(pipefd);
		if (execve(command, *tok_com, *en) == -1)
		{
			if (statu == 1)
				free(command);
			exit(127);
		}
	}
	else
	{
		read_command_output(pipefd, cur_node);
		waitpid(child_pid, &wait_status, 0);
		if (WIFEXITED(wait_status))
			exit_stat = WEXITSTATUS(wait_status);
	}
	return (exit_stat);
}

/**
* createandexesh - executer
* @tokens: strings from stdin
* @cc: user input
* @en: parameters to execve
* @av: user arguments
* @statuss: status of previous loop
* @head: all commands in a line
* @tok_com: ONE command of a line
* @cur_node: current node command
* Return: the process status
*/

int createandexesh(char ***tokens, int *cc, char ***en, char **av,
				   int *statuss, dlistint_t **head, char ***tok_com, dlistint_t *cur_node)
{
	int statu = 0, exit_stat = 0;
	char *command = **tok_com, *trans;

	statu = check_command(tokens, cc, en, av, statuss, head, tok_com,
						  cur_node);
	if (statu != 0 && statu != 1)
	{
		if (statu != 2)
		{
			cur_node->status = statu;
			*statuss = statu;
		}
		return (statu);
	}
	trans = (*tok_com)[0], (*tok_com)[0] = command, command = trans;
	exit_stat = exe_command(statu, en, statuss, tok_com, cur_node, command);
	if (statu == 1)
		free(command);
	*statuss = exit_stat;
	cur_node->status = exit_stat;
	return (exit_stat);
}
