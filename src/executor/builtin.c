#include "../include/minishell.h"

int	cmd_is_builtin(char *cmd)
{
	printf("cmd_is_builtin: %s\n", cmd);
	int			i;
	const char	*builtin[] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};

	if (cmd == NULL)
		return (FALSE);
	i = 0;
	while (builtin[i] != NULL)
	{
		if (cmd == builtin[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	execute_builtin(t_cmd_list *list, char *envp[])
{
	if (list->str[0] == NULL)
		return (EXIT_SUCCESS);
	else if (ft_strncmp(list->str[0], "echo", 4) == 0)
		return (ft_echo(list->str));
	else if (ft_strncmp(list->str[0], "cd", 2) == 0)
		return (EXIT_FAILURE);//(ft_cd(list, envp));
	else if (ft_strncmp(list->str[0], "pwd", 3) == 0)
		return (ft_pwd(list, envp));
	else if (ft_strncmp(list->str[0], "export", 6) == 0)
		return (ft_export(list, envp));
	else if (ft_strncmp(list->str[0], "unset", 5) == 0)
		return (ft_unset(list, envp));
	else if (ft_strncmp(list->str[0], "env", 3) == 0)
		return (ft_env(list, envp));
	else if (ft_strncmp(list->str[0], "exit", 4) == 0)
		return (ft_exit(list));
	else
		return (EXIT_SUCCESS);
}
