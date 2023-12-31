#include "minishell.h"

#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int cmd_is_builtin(char *cmd)
{
    int i;
    const char *builtin[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

    if (cmd == NULL)
        return FALSE;

    i = 0;
    while (builtin[i] != NULL)
    {
        if (strcmp(cmd, builtin[i]) == 0)
            return TRUE;
        i++;
    }

    return FALSE;
}


int	execute_builtin(t_cmdtable *list, char *envp[])
{
	if (list->cmd[0] == NULL)
		return (EXIT_SUCCESS);
	// else if (ft_strncmp(list->str[0], "echo", 4) == 0)
	// 	return (ft_echo(list->str));
	// else if (ft_strncmp(list->str[0], "cd", 2) == 0)
	// 	return (EXIT_FAILURE);//(ft_cd(list, envp));
	// else if (ft_strncmp(list->str[0], "pwd", 3) == 0)
	// 	return (ft_pwd(list, envp));
	// else if (ft_strncmp(list->str[0], "export", 6) == 0)
	// 	return (ft_export(list, envp));
	// else if (ft_strncmp(list->str[0], "unset", 5) == 0)
	// 	return (ft_unset(list, envp));
	else if (ft_strncmp(list->cmd[0], "env", 3) == 0)
		return (ft_env(list, envp));
	// else if (ft_strncmp(list->str[0], "exit", 4) == 0)
	// 	return (ft_exit_changename(list));
	else
		return (EXIT_SUCCESS);
}
