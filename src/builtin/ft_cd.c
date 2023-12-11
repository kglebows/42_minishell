#include "../../includes/minishell.h"

char	*get_path(t_cmd_list *list, char *envp[])
{
	char	*path;

	path = NULL;
	if (list->str[1] == NULL)
	{
		path = ft_getenv("HOME", envp);
		if (path == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
	}
	else if (ft_strncmp(list->str[1], "-", 2) == 0)
	{
		path = ft_getenv("OLDPWD", envp);
		if (path == NULL)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
			return (NULL);
		}
	}
	else
		path = list->str[1];
	return (path);
}

void	update_envp(char *envp[], char *variable, char *value)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], variable, strlen(variable)) != 0)
		i++;
	free(envp[i]);
	envp[i] = ft_strjoin(variable, value);
}

void	ft_cd(t_cmd_list *list, char *envp[])
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	path = get_path(list, envp);
	if (path == NULL)
		return ;
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return ;
	}
	pwd = getcwd(NULL, 0);
	update_envp(envp, "OLDPWD=", oldpwd);
	update_envp(envp, "PWD=", pwd);
	free(oldpwd);
	free(pwd);
	return ;
}
