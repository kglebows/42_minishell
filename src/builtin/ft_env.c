#include "../include/minishell.h"

/**
 * @brief	Executes the builtin command env
 * @param	list The command list struct
 * @param	envp The environment variables
 * @return	EXIT_SUCCESS or EXIT_FAILURE
 */
int	ft_env(t_cmd_list *list, char *envp[])
{
	int	i;

	i = 0;
	if (!list->str[1])
	{
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		printf("env: %s: No such file or directory\n", list->str[1]);
		return (EXIT_FAILURE);
	}
}
