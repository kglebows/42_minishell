/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:29:23 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/03 19:05:52 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Updates the value of an existing environment variable
 * @param node Pointer to the node representing the environment variable
 * @param value New value to set
 * @return 1 on success, 0 on failure
 */
int	update_env(t_env *node, const char *value)
{
	free(node->value);
	node->value = ft_strdup(value);
	return (node->value != NULL);
}

/**
 * @brief Adds a new environment variable node to the linked list
 * @param head Pointer to the head of the environment variable linked list
 * @param new_node Node to add to the linked list
 */
void	add_env_node(t_env **head, t_env *new_node)
{
	t_env	*current;

	current = *head;
	if (*head == NULL)
		*head = new_node;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}
int	ft_fisalnum(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}
int	is_valid_env_name(const char *name)
{
	if (!name || !isalpha(name[0]))
		return (0); // Invalid if name is NULL or does not start with a letter
	for (int i = 1; name[i] != '\0' || name[i] != '='; i++)
	{
		if (ft_fisalnum(name[i]) || name[i] == '-')
			return (0);
	}
	return (1); // Valid environment variable name
}
// int	set_env(t_env **head, char *key_val_str)
// {
// 	t_env	*current;
// 	t_env	*new_node;
// 	char	*eq_sign_pos;

// 	new_node = NULL;
// 	if (!key_val_str)
// 	{
// 		print_env_ascending(*head);
// 		return (EXIT_SUCCESS);
// 	}
// 	eq_sign_pos = ft_strchr(key_val_str, '=');
// 	// if (!eq_sign_pos || eq_sign_pos == key_val_str)
// 	// {
// 	// 	exit_code(1);
// 	// 	ft_putstr_fd("not a valid identifier\n", 2);
// 	// 	return (EXIT_FAILURE);
// 	// }
// 	if (!is_valid_env_name(key_val_str))
// 	{
// 		exit_code(1);
// 		ft_putstr_fd("not a valid identifier\n", 2);
// 		return (EXIT_FAILURE);
// 	}
// 	current = *head;
// 	while (current != NULL)
// 	{
// 		if (!ft_strncmp(current->key, key_val_str, eq_sign_pos - key_val_str))
// 		{
// 			return (update_env(current, eq_sign_pos + 1));
// 		}
// 		current = current->next;
// 	}
// 	new_node = create_env_var_node(key_val_str);
// 	if (!new_node)
// 	{
// 		return (EXIT_FAILURE);
// 	}
// 	add_env_node(head, new_node);
// 	return (EXIT_SUCCESS);
// }
/**
 * @brief Sets or updates an environment variable
 * @param head Pointer to the head of the environment variable linked list

	* @param key_val_str String containing the key-value pair of the environment variable
 * @return 1 on success, 0 on failure
 */
int	set_env(t_env **head, char *key_val_str)
{
	t_env	*current;
	t_env	*new_node;
	char	*eq_sign_pos;

	new_node = NULL;
	if (!key_val_str)
	{
		print_env_ascending(*head);
		return (EXIT_SUCCESS);
	}
	eq_sign_pos = ft_strchr(key_val_str, '=');
	if (eq_sign_pos == key_val_str)
	{
		if (!is_valid_env_name(key_val_str))
		{
			exit_code(1);
			ft_putstr_fd("not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		new_node = create_env_var_node(key_val_str);
	}
	else
	{
		current = *head;
		while (current != NULL)
		{
			if (!ft_strncmp(current->key, key_val_str, eq_sign_pos
					- key_val_str))
				return (update_env(current, eq_sign_pos + 1));
			current = current->next;
		}
		new_node = create_env_var_node(key_val_str);
	}
	if (!new_node)
		return (EXIT_FAILURE);
	add_env_node(head, new_node);
	return (EXIT_SUCCESS);
}

// /**
//  * @brief Sets or updates an environment variable
//  * @param head Pointer to the head of the environment variable linked list

// 	* @param key_val_str String containing the key-value pair of the environment variable
//  * @return 1 on success, 0 on failure
//  */
// int	set_env(t_env **head, char *key_val_str)
// {
// 	t_env	*current;
// 	t_env	*new_node;
// 	char	*eq_sign_pos;

// 	if (!key_val_str)
// 	{
// 		print_env_ascending(*head);
// 		return (EXIT_SUCCESS);
// 	}
// 	eq_sign_pos = ft_strchr(key_val_str, '=');
// 	if (!eq_sign_pos)
// 		return (1);
// 	current = *head;
// 	while (current != NULL)
// 	{
// 		if (!ft_strncmp(current->key, key_val_str, eq_sign_pos - key_val_str))
// 		{
// 			free(current->value);
// 			current->value = ft_strdup(eq_sign_pos + 1);
// 			return (current->value != NULL);
// 		}
// 		current = current->next;
// 	}
// 	new_node = create_env_var_node(key_val_str);
// 	if (!new_node)
// 		return (0);
// 	if (*head == NULL)
// 		*head = new_node;
// 	else
// 	{
// 		current = *head;
// 		while (current->next != NULL)
// 			current = current->next;
// 		current->next = new_node;
// 	}
// 	return (1);
// }
