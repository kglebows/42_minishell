/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:23:32 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/18 11:13:44 by ekordi           ###   ########.fr       */
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

void	print_env_list(t_env *head)
{
	while (head != NULL)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
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

void	swap_nodes(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

int	count_env_variables(t_env *head)
{
	int		count;
	t_env	*current;

	count = 0;
	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	sort_env_linked_list(t_env *head, int count)
{
	int		i;
	t_env	*current;
	t_env	*next;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		current = head;
		next = head->next;
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(current->key, next->key) > 0)
				swap_nodes(current, next);
			current = next;
			next = next->next;
			j++;
		}
		i++;
	}
}

void	print_env_ascending(t_env *head)
{
	int		i;
	int		count;
	t_env	*current;

	current = head;
	count = count_env_variables(current);
	sort_env_linked_list(current, count);
	for (i = 0; i < count; i++)
	{
		if (current->value)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", current->key);
		current = current->next;
	}
}
