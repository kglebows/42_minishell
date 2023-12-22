#include "minishell.h"

/**
 * @brief Executes the 'pwd' command
 * @return 1 on success, 0 on failure
 */
int	execute_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_putstr_fd("Error\n", STDERR_FILENO), 0);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(pwd);
	return (1);
}
/**
 * @brief Executes the 'cd' command
 * @param args Command arguments
 * @return 1 on success, 0 on failure
 */
int	execute_cd(char **args)
{
	char	*tmp;
	char	*tmp2;

	if (args[1] != NULL)
	{
		if (args[1][0] == '~')
		{
			if (chdir(args[1]) != 0)
			{
				perror("chdir");
				return (0);
			}
			return (1);
		}
		else
		{
			tmp = getcwd(NULL, 0);
			if (tmp == NULL)
			{
				perror("getcwd");
				return (0);
			}
			tmp2 = ft_strjoin(tmp, "/");
			free(tmp);
			if (tmp2 == NULL)
				return (0);
			tmp = ft_strjoin(tmp2, args[1]);
			free(tmp2);
			if (tmp == NULL)
				return (0);
			if (chdir(tmp) != 0)
				ft_putstr_fd("Error\n", STDERR_FILENO);
			return (free(tmp), 1);
		}
	}
	else if (chdir(getenv("HOME")))
		ft_putstr_fd("Error\n", STDERR_FILENO);
	return (1);
}
/**
 * @brief Executes the 'echo' command
 * @param args Command arguments
 */
void	execute_echo(char **args)
{
	bool	newline;
	int		i;

	newline = true;
	i = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] == '-' && args[i][1] == 'n' && args[i][2] == '\0')
			newline = false;
		else
		{
			write(STDOUT_FILENO, args[i], strlen(args[i]));
			if (args[i + 1] != NULL)
				write(STDOUT_FILENO, " ", 1);
			else
			{
				i++;
				break ;
			}
		}
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
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

	eq_sign_pos = ft_strchr(key_val_str, '=');
	if (!eq_sign_pos)
	{
		return (1);
	}
	current = *head;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, key_val_str, eq_sign_pos - key_val_str))
		{
			free(current->value);
			current->value = ft_strdup(eq_sign_pos + 1);
			return (current->value != NULL);
		}
		current = current->next;
	}
	new_node = create_env_var_node(key_val_str);
	if (!new_node)
		return (0);
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return (1);
}
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
