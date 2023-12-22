/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:46:27 by ekordi            #+#    #+#             */
/*   Updated: 2023/12/22 12:35:19 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Waits for child processes to finish and sets the exit code
 * @param minishell Pointer to the minishell data structure
 * @param nb_cmd Number of commands
 */
void	ft_waitpid(t_dt *minishell, int nb_cmd)
{
	int	i;
	int	status;

	i = 0;
	while (i < nb_cmd)
		waitpid(minishell->pids[i++], 0, 0);
	waitpid(minishell->pids[i], &status, 0);
	if (WIFEXITED(status))
		exit_code(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		exit_code(128 + WTERMSIG(status));
}
/**
 * @brief Gets the value of an environment variable by name
 * @param env Array of environment variables
 * @param name Name of the environment variable
 * @return Value of the environment variable or NULL if not found
 */

char	*get_env(char **env, const char *name)
{
	size_t	name_len;

	if (env == NULL || name == NULL)
		return (NULL);
	name_len = strlen(name);
	while (*env != NULL)
	{
		if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
			return (*env + name_len + 1);
		env++;
	}
	return (NULL);
}
/**

	* @brief Finds the full path of a command by searching in the PATH environment variable
 * @param cmd Command to find
 * @param env Array of environment variables
 * @return Full path of the command or NULL if not found
 */
char	*cmd_path(char *cmd, char **env)
{
	char	*temp;
	char	**paths;
	int		i;
	char	*path;

	i = 0;
	paths = ft_split(get_env(env, "PATH"), ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i++], "/");
		temp = ft_strjoin(path, cmd);
		if (access(temp, X_OK) == 0)
		{
			free_arrayofstrings(paths);
			free(path);
			return (temp);
		}
		free(temp);
		free(path);
	}
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	free_arrayofstrings(paths);
	return (NULL);
}
/**
 * @brief Opens a file with the specified redirection type
 * @param file Name of the file
 * @param rdr_type Type of redirection
 * @return File descriptor or -1 on failure
 */
int	ft_open(char *file, t_token_type rdr_type)
{
	int	fd = 0;

	if (rdr_type == REDIRECTION_IN)
		fd = open(file, O_RDONLY);
	else if (rdr_type == REDIRECTION_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (rdr_type == REDIRECTION_OUT_APPEND)
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (rdr_type == REDIRECTION_IN_HEREDOC)
		fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			ft_putstr_fd("zsh: permission denied: ", 2);
		else if (errno == ENOENT)
			ft_putstr_fd("zsh: no such file or directory: ", 2);
		else
			ft_putstr_fd("zsh: error opening the file: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
	}
	return (fd);
}
