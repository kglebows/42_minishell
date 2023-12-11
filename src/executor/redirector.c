#include "minishell.h"

int	set_outfile(t_cmd_list *list)
{
	int		fd;
	char	*file;

	file = list->redirect_list->file;
	printf("Outfile: %s\n", file);
	fd = open (file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		exit(1);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
		ft_close_fd (fd);
	}
	return (EXIT_SUCCESS);
}

int	set_infile(t_cmd_list *list)
{
	int	fd;
	char	*file;

	file = list->redirect_list->file;
	printf("Infile: %s\n", file);
	fd = open (file, O_RDWR, 0644);
	if (fd < 0)
	{
		exit (1);
	}
	else
	{
		//list->in = fd;
		if (dup2(fd, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		close (fd);
	}
	return (EXIT_SUCCESS);
}

int	append_file(char *file)
{
	int	fd;

	fd = open (file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		exit (1);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
		close (fd);
	}
	return (EXIT_SUCCESS);
}

int	is_valid_redirection(t_redirect redirection)
{
	if (redirection)
		return (TRUE);
	return (FALSE);
}

void	check_redirections(t_cmd_list *list)
{
	printf("redirection %i\n", list->redirect_list->redirection);
	if (list->redirect_list->redirection == infile)
		set_infile(list);
	else if (list->redirect_list->redirection == outfile)
		set_outfile(list);
	/* else if (list->redirect_list->redirection == here_doc)
		create_heredoc();
	else if (list->redirect_list->redirection == append)
		append_file(list->file); */
	else
		printf("nothing to redirect\n");
}
