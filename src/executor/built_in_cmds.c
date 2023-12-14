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
