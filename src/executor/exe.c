/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:55:02 by ekordi            #+#    #+#             */
/*   Updated: 2023/12/15 17:03:28 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_and_execute(t_dt *minishell)
{
	int		i;
	int		nb_cmd;
	bool	last_cmd;

	i = 0;
	nb_cmd = 0;
	while (minishell->cmdtable[nb_cmd])
		nb_cmd++;

	while (i < nb_cmd)
	{
		minishell->cmdtable[i]->fd_rdr_out = 0;
		check_redirections(minishell->cmdtable[i]);
		if (i + 1 == nb_cmd)
			last_cmd = true;
		execute(minishell->cmdtable[i], minishell->cmdtable[i]->cmd, minishell->envp, last_cmd);
		i++;
	}

	// int status;
	// waitpid(pid, &status, 0);
	// if (WIFEXITED(status))
	// 	//upodate exit code
	// if (WIFSIGNALED(status))
	// 	exit_code(status);
	return (1);
}

void	free_arrayofstrings(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}
char	*get_env(char **env, const char *name)
{
	size_t	name_len;

	if (env == NULL || name == NULL)
		return (NULL);
	name_len = strlen(name);
	while (*env != NULL)
	{
		if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
			return (*env + name_len + 1);
		env++;
	}
	return (NULL);
}
char	*cmd_path(char *cmd, char **env)
{
	char	*temp;
	char	**paths;
	int		i;
	char	*path;

	i = 0;
	paths = ft_split(get_env(env, "PATH"), ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i++], "/");
		temp = ft_strjoin(path, cmd);
		if (access(temp, X_OK) == 0)
		{
			free_arrayofstrings(paths);
			free(path);
			return (temp);
		}
		free(temp);
		free(path);
	}
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	free_arrayofstrings(paths);
	return (NULL);
}

void	execute(t_cmdtable *table, char **args, char **env, bool last_cmd)
{
	char	*path;
	int		pid1;
	int		fd[2];
	int		r;

	if (access(args[0], X_OK) == 0)
		path = args[0];
	else
		path = cmd_path(args[0], env);
	if (path == NULL)
		ft_putstr_fd("Path Error\n", 2);
	if (pipe(fd) == -1)
		ft_putstr_fd("Pipe Error\n", 2);

	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (table->fd_rdr_out)
				dup2(table->fd_rdr_out, STDOUT_FILENO);
		if (last_cmd && !table->fd_rdr_out)
			dup2(table->fd_out, STDOUT_FILENO);

		r = exe_built_in_cmds(args, env);
		if (r == 1)
			exit(0); // execution was succsesful
		else if (r == 0)
		{
			if (execve(path, args, env) == -1)
				ft_putstr_fd("Exec Error", 2);
		}
	}
	else
	{
		table->fd_rdr_out = 0;
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		if (last_cmd)
			dup2(table->fd_in, STDIN_FILENO);
		waitpid(pid1, NULL, 0);
	}
}

int	exe_built_in_cmds(char **args, char **env)
{
	if (!ft_strncmp(args[0], "echo", 4) && ft_strlen(args[0]) == 4)
	{
		execute_echo(args + 1);
		return (1);
	}
	else if (!ft_strncmp(args[0], "pwd", 3) && ft_strlen(args[0]) == 3)
	{
		if (!execute_pwd())
			return (-2);
		else
			return (1);
	}
	else if (!ft_strncmp(args[0], "cd", 2) && ft_strlen(args[0]) == 2)
	{
		if (!execute_cd(args))
			return (-2);
		else
			return (1);
	}
	// else if (!ft_strncmp(args[0], "export", 6) && ft_strlen(args[0]) == 6)
	// {
	// 	if (args[1] && !set_env(&env, args[1]))
	// 		return (-2);
	// 	else
	// 		return (1);
	// }
	// else if (!ft_strncmp(args[0], "unset", 5) && ft_strlen(args[0]) == 5)
	// {
	// 	if (args[1] && cmd->is_param)
	// 		unset_env(&env, cmd->value);
	// 	return (1);
	// }
	else if (!ft_strncmp(args[0], "env", 3) && ft_strlen(args[0]) == 3)
	{
		print_env_var_list(env);
		return (1);
	}
	return (0);
}
