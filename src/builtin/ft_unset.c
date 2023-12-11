#include "../../includes/minishell.h"
#include "../../includes/executor.h"

/**
 * @brief	Executes the builtin command unset
 * @param	list The command list struct
 * @param	envp The environment variables
 * @return	EXIT_SUCCESS or EXIT_FAILURE
 */
int	ft_unset(t_cmd_list *list, char *envp[])
{
	int	i;

	i = 0;
	if (!list->str[1])
	{
		printf("unset: not enough arguments\n");
		return (EXIT_FAILURE);
	}
	else
	{
		while (list->str[i])
		{
			if (ft_strchr(list->str[i], '='))
			{
				printf("unset: `%s': not a valid identifier\n", list->str[i]);
				return (EXIT_FAILURE);
			}
			else
				ft_unsetenv(list->str[i], envp);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief	Removes an environment variable from the environment
 * @param	str The environment variable to remove
 * @param	envp The environment variables
 * @return	EXIT_SUCCESS or EXIT_FAILURE
 */
int	ft_unsetenv(char *str, char *envp[])
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)))
		{
			new_envp[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	free(str);
	free(envp);
	envp = new_envp;
	return (EXIT_SUCCESS);
}
