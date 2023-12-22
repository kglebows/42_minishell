/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:53:28 by ekordi            #+#    #+#             */
/*   Updated: 2023/12/22 12:31:15 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a heredoc file
 * @param delimiter The delimiter of the heredoc (e.g., EOF)
 * @return File descriptor to the heredoc file on success,
	EXIT_FAILURE on failure
 */
int	create_heredoc(char *delimiter)
{
	int		fd;
	char	*line;

	fd = ft_open("heredoc", REDIRECTION_IN_HEREDOC);
	if (fd == -1)
		return (EXIT_FAILURE);
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	fd = ft_open("heredoc", REDIRECTION_IN);
	if (fd == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
/**
 * @brief Sets the output file for a command table
 * @param table Pointer to the command table
 * @param file Name of the output file
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int	set_outfile(t_cmdtable *table, char *file)
{
	table->fd_rdr_out = ft_open(file, REDIRECTION_OUT);
	if (table->fd_rdr_out < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
/**
 * @brief Sets the input file for a command table
 * @param table Pointer to the command table
 * @param file Name of the input file
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int	set_infile(t_cmdtable *table, char *file)
{
	table->fd_rdr_in = ft_open(file, REDIRECTION_IN);
	if (table->fd_rdr_in < 0)
		return (EXIT_FAILURE);
	else
	{
		if (dup2(table->fd_rdr_in, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		close(table->fd_rdr_in);
	}
	return (EXIT_SUCCESS);
}
/**
 * @brief Appends the output to a file for a command table
 * @param file Name of the output file to append
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int	append_file(char *file)
{
	int	fd;

	fd = ft_open(file, REDIRECTION_OUT_APPEND);
	if (fd < 0)
		return (EXIT_FAILURE);
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
		close(fd);
	}
	return (EXIT_SUCCESS);
}
/**
 * @brief Checks and applies redirections for a command table
 * @param table Pointer to the command table
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int	check_redirections(t_cmdtable *table)
{
	int	i;
	int	exit_status;

	i = 0;
	if (table->rdr_nb)
	{
		while (i < table->rdr_nb)
		{
			if (table->rdr[i].type == REDIRECTION_IN)
				exit_status = set_infile(table, table->rdr[i].data);
			else if (table->rdr[i].type == REDIRECTION_OUT)
				exit_status = set_outfile(table, table->rdr[i].data);
			else if (table->rdr[i].type == REDIRECTION_IN_HEREDOC)
			{
				if (create_heredoc(table->rdr[i].data))
					exit_status = set_infile(table, "heredoc");
			}
			else if (table->rdr[i].type == REDIRECTION_OUT_APPEND)
				exit_status = append_file(table->rdr[i].data);
			if (exit_status)
				return (EXIT_FAILURE);
			i++;
		}
	}
	return(EXIT_SUCCESS);
}
