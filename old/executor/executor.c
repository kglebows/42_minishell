#include "minishell.h"

//static int	execute_child(t_cmd_list *list, int fd_in, char *envp[]);
//static void	execute(t_cmd_list *list, char *envp[]);

//void	executor(t_cmdtable *list, char *envp[], t_shell_context *c)
void	executor(t_cmdtable *list, char *envp[])
{
	int		fd;
	int		i;
	int		total;

	if (cmd_is_builtin(list->cmd[0]) == TRUE)
	{
		printf("BUILTIN\n");
		execute_builtin(list, envp);
		return ;
	}
	else
	{
		total = 2;
		i = 0;
		fd = list->fd_in;
		while (i < total)
		{
			check_redirections(list);
			fd = execute_child(list, fd, envp);
			list = list->next;
			i++;
		}
		i = 0;
		while (i < c->pipes)
			waitpid(c->pids[i++], 0, 0);
		close(fd);
		//set_g_error(status);
	}
	return ;
}

static void	execute(t_cmd *list, char *envp[])
{
	char	*path;

	if (list != NULL)
	{
		path = list->cmd;
		path = find_cmd_path(envp, list->str[0]);
		//printf("PATH: %s\n", path);
		execve(path, list->str, NULL);
	}
	exit(1);
}

static int	execute_child(t_cmd_list *list, int fd_in, char *envp[])
{
	int			fd[2];
	pid_t		pid;

	pipe(fd);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		dup_input(fd_in, list);
		dup_output(fd[1], list);
		close_all_fds(fd[0], fd[1], 0);
		close_all_fds(list->in, list->out, fd_in);
		execute(list, envp);
	}
	close_all_fds(list->in, list->out, fd_in);
	close(fd[1]);
	return (fd[0]);
}
