#include "minishell.h"
int	ft_open(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			ft_putstr_fd("zsh: permission denied: ", 2);
		else if (errno == ENOENT)
			ft_putstr_fd("zsh: no such file or directory: ", 2);
		else
			ft_putstr_fd("zsh: error opening the file: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd("\n", 2);
	}
	return (fd);
}
int	set_outfile(t_cmdtable *table, char *file)
{
	//printf("Outfile: %s\n", file);
	table->fd_rdr_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (table->fd_rdr_out < 0)
		exit(1);
	// else
	// {
	// 	// if (dup2(table->fd_rdr_out, STDOUT_FILENO) == -1)
	// 	// 	return (EXIT_FAILURE);
	// 	if (table->fd_rdr_out > STDERR_FILENO)
	// 			close(table->fd_rdr_out);
	// }
	return (EXIT_SUCCESS);
}

int	set_infile(t_cmdtable *table, char *file)
{
	//printf("Infile: %s\n", file);
	table->fd_rdr_in = ft_open(file);
	if (table->fd_rdr_in < 0)
		exit (1);
	else
	{
		//list->in = fd;
		if (dup2(table->fd_rdr_in, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		close (table->fd_rdr_in);
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

void	check_redirections(t_cmdtable *table)
{
	int i = 0;
	if (table->rdr_nb)
	{
		while (i < table->rdr_nb)
		{
			if (table->rdr[i].type == REDIRECTION_IN)
				set_infile(table, table->rdr[i].data);
			else if (table->rdr[i].type == REDIRECTION_OUT)
				set_outfile(table, table->rdr[i].data);
			i++;
		}
	}



	/* else if (list->redirect_list->redirection == here_doc)
		create_heredoc();
	else if (list->redirect_list->redirection == append)
		append_file(list->file); */
	// else
	// 	printf("nothing to redirect\n");
}
