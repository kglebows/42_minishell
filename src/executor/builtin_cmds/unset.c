/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:30:39 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/17 23:58:17 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Unsets an environment variable
 * @param head Pointer to the head of the environment variable linked list
 * @param var Variable to unset
 * @return 1 if the variable was unset, 0 if the variable was not found
 */

int	var_validate(char *var)
{
	if (var == NULL || (var[0] == '\0' || var[0] == '=' || var[0] == '?'
			|| (var[0] == '$' && var[1] == '\0')))
		return (0);
	return (1);
}

void	unset(t_env **head, char **var)
{
	int	i;

	i = 1;
	while (var[i])
	{
		if (var_validate(var[i]))
		{
			unset_env(head, var[i]);
		}
		else
		{
			exit_code(1);
			printf("error\n");
		}
		i++;
	}
}

int	unset_env(t_env **head, char *var)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, var, ft_strlen(var)))
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
