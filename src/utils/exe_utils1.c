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
		printf("Key: %s, Value: %s\n", head->key, head->value);
		head = head->next;
	}
}
/**
 * @brief Creates a new node for an environment variable
 * @param str String containing the key-value pair of the environment variable
 * @return Pointer to the newly created node on success, NULL on failure
 */
// t_env	*create_env_var_node(char *str)
// {
// 	char	*eq_sign_pos;
// 	t_env	*node;

// 	eq_sign_pos = ft_strchr(str, '=');
// 	if (!eq_sign_pos)
// 		return (NULL);
// 	node = (t_env *)malloc(sizeof(t_env));
// 	if (!node)
// 		return (NULL);
// 	node->next = NULL;
// 	node->key = ft_strgetbetween(str, eq_sign_pos - 1);
// 	if (!node->key)
// 		return (free(node), NULL);
// 	node->value = ft_strdup(eq_sign_pos + 1);
// 	if (!node->value)
// 		return (free(node->key), free(node), NULL);
// 	return (node);
// }
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
/// @brief Sorts the given linked list in by ascii values
/// @param array The array to sort
/// @param count The length of the array
static void	sort_env_linked_list(t_env **array, int count)
{
	t_env	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(array[j]->key, array[j + 1]->key) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
/// @brief Counts the number of env variables stored in the linked list
/// @param head A pointer to the first node in the linked list
/// @return The amount of env variables stored in the linked list.
int	count_env_variables(t_env *head)
{
	int		i;
	t_env	*temp;

	temp = head;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

/// @brief Converts the given env linked list into an array
/// @param head The head pointer
/// @param array The array to assign data to
static void	assign_array(t_env *head, t_env **array)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = head;
	while (temp)
	{
		array[i] = temp;
		temp = temp->next;
		i++;
	}
}

/// @brief Prints the env linked list in ascending order and with the export
/// format.
/// @param head The head node of the env linked list.
void	print_env_ascending(t_env *head)
{
	t_env	**array;
	int		i;
	int		count;

	i = 0;
	count = count_env_variables(head);
	array = (t_env **)ft_calloc(count, sizeof(t_env *));
	if (!array)
		return ;
	assign_array(head, array);
	sort_env_linked_list(array, count);
	while (count)
	{
		if (array[i]->value)
			ft_printf("declare -x %s=\"%s\"\n", array[i]->key, array[i]->value);
		else
			ft_printf("declare -x %s\n", array[i]->key);
		i++;
		count--;
	}
	free(array);
}
