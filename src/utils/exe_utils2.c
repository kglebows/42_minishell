/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:42:42 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/02 14:22:58 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_array(t_env *head, char **array)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = head;
	while (temp)
	{
		array[i] = (char *)malloc(strlen(temp->key) + strlen(temp->value) + 2);
		ft_strlcpy(array[i], temp->key, strlen(temp->key) + 1);
		ft_strlcat(array[i], "=", strlen(array[i]) + 2);
		ft_strlcat(array[i], temp->value, strlen(array[i]) + strlen(temp->value)
			+ 1);
		temp = temp->next;
		i++;
	}
	array[i] = NULL;
}

char	**env_to_char_array(t_env *head)
{
	int		count;
	char	**result;

	count = count_env_variables(head);
	result = (char **)malloc((count + 1) * sizeof(char *));
	assign_array(head, result);
	return (result);
}

// static void	assign_array(t_env *head, char **array)
// {
// 	int		i;
// 	t_env	*temp;

// 	i = 0;
// 	temp = head;
// 	while (temp)
// 	{
// 		array[i] = (char *)malloc(strlen(temp->key) + strlen(temp->value) + 2);
// 		sprintf(array[i], "%s=%s", temp->key, temp->value);
// 		temp = temp->next;
// 		i++;
// 	}
// 	array[i] = NULL;
// }

// char	**env_to_char_array(t_env *head)
// {
// 	int		count;
// 	char	**result;

// 	count = count_env_variables(head);
// 	result = (char **)malloc((count + 1) * sizeof(char *));
// 	assign_array(head, result);
// 	return (result);
// }
char	*find_path(t_cmdtable *table, char **env, bool last_cmd)
{
	char		*temp;
	struct stat	path_stat;

	temp = NULL;
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

int	update_env_value(t_env *head, const char *key, const char *new_value)
{
	t_env	*current;

	if (head == NULL || key == NULL || new_value == NULL)
		return (0);
	current = head;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = strdup(new_value);
			if (current->value == NULL)
				return (0);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	print_env_var_list(char **env)
{
	if (env == NULL)
		return ;
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
