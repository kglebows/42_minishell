#include "minishell.h"

char	*ft_strgetbetween(const char *start, const char *end)
{
	char	*word;
	size_t	i;
	if ((*start == '\'' && *end == '\'') || (*start == '"' && *end == '"'))
	{
		start++;
		end--;
	}
	word = (char *)malloc((end - start + 2) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (*start && start <= end)
	{
		word[i] = *start;
		start++;
		i++;
	}
	word[i] = '\0';
	return (word);
}
/**
 * @brief Creates a new node for an environment variable
 * @param str String containing the key-value pair of the environment variable
 * @return Pointer to the newly created node on success, NULL on failure
 */
static t_env	*create_env_var_node(char *str)
{
	char	*eq_sign_pos;
	t_env	*node;
	eq_sign_pos = ft_strchr(str, '=');
	if (!eq_sign_pos)
		return (NULL);
	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->key = ft_strgetbetween(str, eq_sign_pos - 1);
	if (!node->key)
		return (free(node), NULL);
	node->value = ft_strdup(eq_sign_pos + 1);
	if (!node->value)
		return (free(node->key), free(node), NULL);
	return (node);
}

void	free_env_var_list(t_env *head)
{
	t_env	*temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

t_env	*init_env_var(char *envp[])
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;
	int		i;
	head = NULL;
	tail = NULL;

	i = 0;
	while (envp[i++] != NULL)
	{
		new_node = create_env_var_node(envp[i - 1]);
		if (new_node == NULL)
			return (free_env_var_list(head), NULL);
		if (tail == NULL)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
	}
	return (head);
}

void	test_print_envlist(t_dt *dt)
{
	t_env			*temp;
	int				u;

	u = 1;
	temp = dt->envp_lst;
	printf(":::::::::::::::::: env ::::::::::::::::::::\n");
	while (temp)
	{
		printf("%2d :: %-30s :: %s\n", u, temp->key, temp->value);
		temp = temp->next;
		u++;
	}
	printf(":::::::::::::::::::::::::::::::::::::::::::\n");
}