/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:30:39 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/17 19:23:25 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Unsets an environment variable
 * @param head Pointer to the head of the environment variable linked list
 * @param var Variable to unset
 * @return 1 if the variable was unset, 0 if the variable was not found
 */
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
