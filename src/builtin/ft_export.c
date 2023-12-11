#include "../../includes/minishell.h"
#include "../../includes/executor.h"

//This function is used to execute the export command
int	ft_export(t_cmd_list *list, char *envp[])
{
	int	i;

	i = 0;
	if (!list->str[1])
	{
		while (envp[i])
		{
			printf("declare -x %s\n", envp[i]);
			i++;
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		printf("export: %s: not a valid identifier\n", list->str[1]);
		return (EXIT_FAILURE);
	}
}