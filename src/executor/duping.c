#include "../../includes/minishell.h"
#include "../../includes/executor.h"

void	dup_output(int outpipe, t_cmd_list *list)
{
	if (list->out == STDOUT_FILENO)
	{
		if (list->next == NULL)
			dup2(STDOUT_FILENO, STDOUT_FILENO);
		else
			dup2(outpipe, STDOUT_FILENO);
	}
	else
		dup2(list->out, STDOUT_FILENO);
}

void	dup_input(int inpipe, t_cmd_list *list)
{
	if (list->in == STDIN_FILENO)
	{
		if (list->prev == NULL)
			dup2(STDIN_FILENO, STDIN_FILENO);
		else
			dup2(inpipe, STDIN_FILENO);
	}
	else
		dup2(list->in, STDIN_FILENO);
}

void	ft_close_fd(int fd)
{
	if (fd > STDERR_FILENO)
		close(fd);
}

void	close_all_fds(int fd1, int fd2, int fd3)
{
	ft_close_fd(fd1);
	ft_close_fd(fd2);
	ft_close_fd(fd3);
}
