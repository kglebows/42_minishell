/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:55:02 by ekordi            #+#    #+#             */
/*   Updated: 2023/12/22 12:58:44 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prepares and executes commands in the minishell
 * @param minishell Pointer to the minishell data structure
 * @return 1 on success
 */
int	prepare_and_execute(t_dt *minishell)
{
	int		i;
	int		nb_cmd;
	bool	last_cmd;

	i = 0;
	nb_cmd = 0;
	while (minishell->cmdtable[nb_cmd])
		nb_cmd++;
	minishell->pids = ft_calloc(sizeof(int), nb_cmd + 1);
	minishell->pids[nb_cmd] = 0;
	while (i < nb_cmd)
	{
		if (i + 1 == nb_cmd)
			last_cmd = true;
		minishell->cmdtable[i]->fd_rdr_out = 0;
		if (check_redirections(minishell->cmdtable[i]))
		{
			if (last_cmd)
			{
				exit_code(1);
				exit(1);
			}
			else
			{	minishell->cmdtable[i]->fd_rdr_in = 0;
				i++;
				continue ;
			}
		}
		execute(minishell->cmdtable[i], minishell, last_cmd);
		i++;
	}
	//ft_waitpid(minishell, nb_cmd);
	return (1);
}
/**
 * @brief Executes a child process for a command table
 * @param table Pointer to the command table
 * @param env Environment variables
 * @param last_cmd Flag indicating if this is the last command in a pipeline
 * @param envp_lst Linked list of environment variables
 */
void	child(t_cmdtable *table, char **env, bool last_cmd, t_env *envp_lst)
{
	char	*path;

	if (table->fd_rdr_out)
		dup2(table->fd_rdr_out, STDOUT_FILENO);
	if (last_cmd && !table->fd_rdr_out)
		dup2(table->fd_out, STDOUT_FILENO);
	if (exe_built_in_cmds(table->cmd, env, envp_lst) == 1)
		exit(EXIT_SUCCESS);
	else
	{
		if (access(table->cmd[0], X_OK) == 0)
			path = table->cmd[0];
		else
			path = cmd_path(table->cmd[0], env);
		if (execve(path, table->cmd, env) == -1)
			ft_putstr_fd("Exec Error", 2);
	}
}
/**
 * @brief Executes a command table in the minishell
 * @param table Pointer to the command table
 * @param minishell Pointer to the minishell data structure
 * @param last_cmd Flag indicating if this is the last command in a pipeline
 */
void	execute(t_cmdtable *table, t_dt *minishell, bool last_cmd)
{
	int	pid1;
	int	fd[2];

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
		child(table, minishell->envp, last_cmd, minishell->envp_lst);
	}
	else
	{
		table->fd_rdr_out = 0;
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		if (last_cmd)
			dup2(table->fd_in, STDIN_FILENO);
		waitpid(pid1, 0, 0);// to be deleted
	}
}
/**
 * @brief Executes built-in commands or external executables
 * @param args Command arguments
 * @param env Environment variables
 * @param envp_lst Linked list of environment variables
 * @return 1 if the command was executed successfully,
	0 if not a built-in command, -1 on error
 */
int	exe_built_in_cmds(char **args, char **env, t_env *envp_lst)
{
	if (!ft_strncmp(args[0], "echo", 4) && ft_strlen(args[0]) == 4)
		execute_echo(args + 1);
	else if (!ft_strncmp(args[0], "pwd", 3) && ft_strlen(args[0]) == 3)
	{
		if (!execute_pwd())
			return (-1);
	}
	else if (!ft_strncmp(args[0], "cd", 2) && ft_strlen(args[0]) == 2)
	{
		if (!execute_cd(args))
			return (-1);
	}
	else if (!ft_strncmp(args[0], "export", 6) && ft_strlen(args[0]) == 6)
	{
		if (args[1] && !set_env(&envp_lst, args[1]))
			return (-1);
	}
	else if (!ft_strncmp(args[0], "unset", 5) && ft_strlen(args[0]) == 5)
	{
		if (args[1])
			unset_env(&envp_lst, args[1]);
	}
	else if (!ft_strncmp(args[0], "env", 3) && ft_strlen(args[0]) == 3)
		print_env_var_list(env);
	else
		return (0);
	return (1);
}
