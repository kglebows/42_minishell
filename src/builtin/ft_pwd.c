#include "../../includes/minishell.h"
#include "../../includes/executor.h"

int	ft_pwd(t_cmd_list *list, char *envp[])
{
	char	*pwd;

	(void)envp;
	if (!list->str[1])
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
		free(pwd);
		return (EXIT_SUCCESS);
	}
	else
	{
		printf("pwd: too many arguments\n");
		return (EXIT_FAILURE);
	}
}