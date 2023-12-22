#include "minishell.h"

/**
 * @brief Duplicates the output of the current command to the next command
 * @param list The current command
 * @param outpipe the file descriptor of the pipe
 * @return
*/
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

/**
 * @brief Duplicates the output of the current command to the next command
 * @param list The current command
 * @param inpipe the file descriptor of the pipe
 * @return
*/
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

/**
 * @brief Closes one file descriptor, when not needed anymore
 * @param fd One file descriptor
 * @return
*/
void	ft_close_fd(int fd)
{
	if (fd > STDERR_FILENO)
		close(fd);
}

/**
 * @brief Closes multiple file descriptors, when they are not needed anymore
 * @param fd1 One file descriptor
 * @param fd2 Another file descriptor
 * @param fd3 Another file descriptor
 * @return
*/
void	close_all_fds(int fd1, int fd2, int fd3)
{
	ft_close_fd(fd1);
	ft_close_fd(fd2);
	ft_close_fd(fd3);
}
