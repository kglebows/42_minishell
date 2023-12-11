#include "../../includes/minishell.h"
#include "../../includes/executor.h"

/**
 * @brief	Executes the builtin command exit - exits with a status
 * @param	list The command list struct
 * @return	EXIT_SUCCESS or EXIT_FAILURE
 */
int	ft_exit(t_cmd_list *list)
{
	int	i;

	i = 0;
	if (!list->str[1])
		exit(EXIT_SUCCESS);
	else if (list->str[1] && list->str[2])
		return (printf("exit\nminishell: exit: too many arguments\n"),
			EXIT_FAILURE);
	else
	{
		while (list->str[1][i])
		{
			if (!ft_isdigit(list->str[1][i]))
			{
				printf("exit\nminishell: exit: %s: numeric argument required\n",
					list->str[1]);
				exit(EXIT_FAILURE);
			}
			i++;
		}
		exit(ft_atoi(list->str[1]));
	}
	return (EXIT_SUCCESS);
}
