#include "../include/minishell.h"

char	*find_cmd_path(char *envp[], char *argv)
{
	char	**path;
	char	**cmd;
	char	*acc1;
	char	*acc2;
	int		i;

	i = 0;
	acc2 = NULL;
	if (ft_strnstr(argv, "/", ft_strlen(argv)))
		return (ft_strdup(argv));
	cmd = ft_split(argv, ' ');
	path = find_path(envp);
	while (path && path[i] != NULL)
	{
		acc1 = ft_strjoin("/", cmd[0]);
		acc2 = ft_strjoin(path[i++], acc1);
		free(acc1);
		if (access(acc2, F_OK) == 0)
			break ;
		free(acc2);
		acc2 = NULL;
	}
	if ((access(acc2, F_OK) != 0) && argv[0] == '.')
		acc2 = ft_strdup(argv);
	return (free_double_char(cmd), free_double_char(path), acc2);
}

char	**find_path(char *envp[])
{
	int		i;
	char	**path;
	char	*env;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_memcmp(envp[i], "PATH=", 5) == 0)
		{
			env = ft_strtrim(envp[i], "PATH=");
			path = ft_split(env, ':');
			free(env);
			return (path);
		}
		i++;
	}
	return (NULL);
}
