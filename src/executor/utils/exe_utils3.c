/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:54:59 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/20 14:57:08 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees memory allocated for an array of strings
 * @param array Array of strings
 */
void	free_arrayofstrings(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*find_path(t_cmdtable *table, char **env, bool last_cmd)
{
	char		*temp;
	struct stat	path_stat;

	temp = NULL;
	(void)last_cmd;
	if (stat(table->cmd[0], &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd(table->cmd[0], STDERR_FILENO);
			ft_putstr_fd(" is a directory\n", STDERR_FILENO);
			temp = NULL;
		}
	}
	if (access(table->cmd[0], X_OK) == 0)
		temp = table->cmd[0];
	else
		temp = cmd_path(table->cmd[0], env);
	if (!temp)
	{
		if (last_cmd)
			dup2(table->fd_in, STDIN_FILENO);
		exit(127);
	}
	return (temp);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (-2);
	while (s1[i] && s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
