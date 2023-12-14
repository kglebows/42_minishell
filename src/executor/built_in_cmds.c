#include "minishell.h"

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

// int	set_env(t_env **head, char *key_val_str)
// {
// 	t_env	*current;
// 	t_env	*new_node;
// 	char	*eq_sign_pos;

// 	eq_sign_pos = ft_strchr(key_val_str, '=');
// 	if (!eq_sign_pos)
// 	{
// 		return (1);
// 	}
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
