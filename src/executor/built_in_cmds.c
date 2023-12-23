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

void print_env_list(t_env *head) {
    while (head != NULL) {
        printf("Key: %s, Value: %s\n", head->key, head->value);
        head = head->next;
    }
}
int update_env_value(t_env *head, const char *key, const char *new_value) {
    if (head == NULL || key == NULL || new_value == NULL) {
        // Invalid input
        return 0;
    }

    t_env *current = head;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // Key found, update the value
            free(current->value);  // Free existing value
            current->value = strdup(new_value);  // Update value

            if (current->value == NULL) {
                // Memory allocation failure
                return 0;
            }

            // Update successful
            return 1;
        }

        current = current->next;
    }

    // Key not found
    return 0;
}

int	execute_cd(char **args, t_env *envp_list)
{
	char	*tmp;
	char	*tmp2;
	char	*old_pwd;

	if (args[1] != NULL)
	{
		if (args[1][0] == '~')
		{
			if (chdir(args[1]) != 0)
			{
				perror("chdir");
				return (0);
			}
		}
		else
		{
			tmp = getcwd(NULL, 0);
			old_pwd = getcwd(NULL, 0);
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
			free(tmp);

		}
	}
	else if (chdir(getenv("HOME")) != 0)
	{
		perror("chdir");
		ft_putstr_fd("Error\n", STDERR_FILENO);
		return (0);
	}

	// Update the PWD environment variable
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		perror("getcwd");
		return (0);
	}
	//print_env_list(envp_list);
	update_env_value(envp_list, "PWD", tmp);
	update_env_value(envp_list, "OLDPWD", old_pwd);
	free(tmp);
	free(old_pwd);
	print_env_list(envp_list);

	return (1);
}

/**
 * @brief Executes the 'echo' command
 * @param args Command arguments
 */
void	execute_echo(char **args)
{
	bool	newline;
	bool	endofn;
	int		i;
	int		n;

	newline = true;
	endofn = false;
	i = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] == '-' && args[i][ft_strlen(args[i])] == '\0'
			&& endofn == false)
		{
			n = 1;
			while (n < ft_strlen(args[i]))
			{
				if (args[i][n] != 'n')
				{
					endofn = true;
					i--;
					break ;
				}
				n++;
			}
			if (n == ft_strlen(args[i]))
				newline = false;
		}
		else
		{
			endofn = true;
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
