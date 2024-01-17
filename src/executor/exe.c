
#include "minishell.h"

/**
 * @brief Prepares and executes commands in the minishell
 * @param minishell Pointer to the minishell data structure
 * @return 1 on success
 */
int	prepare_and_execute(t_dt *minishell)
{
	int		i;
	int		table_num;
	bool	last_cmd;

	i = -1;
	table_num = 0;
	while (minishell->cmdtable[table_num])
	{
		table_num++;
	}
	if (minishell->cmdtable[0]->cmd_nb != 0 && table_num == 1
		&& !ft_strncmp(minishell->cmdtable[0]->cmd[0], "exit", 4))
	{
		exit_shell(minishell->cmdtable[0]->cmd);
		return (1);
	}
	while (++i < table_num)
	{
		if (i + 1 == table_num)
			last_cmd = true;
		execute(minishell->cmdtable[i], minishell, last_cmd);
	}
	ft_waitpid(minishell, table_num);
	return (1);
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
	int	exit_code;

	if (pipe(fd) == -1)
		ft_putstr_fd("Pipe Error\n", 2);
	if (table->cmd[0])
		exit_code = exe_parent_builtin_cmds(table, minishell);
	// if (table->cmd[0][0] == '\0')
	// {
	// //printf("NULL\n");
	// 	exit_code = 1;
	// 	/* code */
	// }
	block_signal();
	pid1 = fork();
	table->fd_rdr_out = 0;
	if (pid1 == 0)
	{
		setup_child_signals();
		if (exit_code == EXIT_FAILURE)
			exit(exit_code);
		child(table, last_cmd, minishell->envp_lst, fd);
	}
	else
	{
		table->fd_rdr_out = 0;
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		if (last_cmd)
			dup2(table->fd_in, STDIN_FILENO);
	}
}

void	child(t_cmdtable *table, bool last_cmd, t_env *envp_lst, int *fd)
{
	char	*path;

	close(fd[0]);
	if (check_redirections(table, fd) && table->cmd)
		exit(1);
	else
	{
		dup2(fd[1], STDOUT_FILENO);
		if (table->fd_rdr_out)
			dup2(table->fd_rdr_out, STDOUT_FILENO);
		if (last_cmd && !table->fd_rdr_out)
			dup2(table->fd_out, STDOUT_FILENO);
		if (exe_built_in_cmds(table->cmd, envp_lst))
			exit(EXIT_SUCCESS);
		else
		{
			path = find_path(table, env_to_char_array(envp_lst), last_cmd);
			execve(path, table->cmd, env_to_char_array(envp_lst));
		}
	}
}

int	exe_parent_builtin_cmds(t_cmdtable *table, t_dt *minishell)
{
	if (!ft_strncmp(table->cmd[0], "cd", 2) && ft_strlen(table->cmd[0]) == 2)
	{
		execute_cd(table->cmd, minishell->envp_lst);
	}
	else if (!ft_strncmp(table->cmd[0], "export", 6)
		&& ft_strlen(table->cmd[0]) == 6)
	{
		if (set_env(&minishell->envp_lst, table->cmd))
			return (1);
	}
	else if (!ft_strncmp(table->cmd[0], "unset", 5)
		&& ft_strlen(table->cmd[0]) == 5)
	{
		if (table->cmd[1])
			unset_env(&minishell->envp_lst, table->cmd[1]);
	}
	return (0);
}

int	exe_built_in_cmds(char **args, t_env *envp_lst)
{
	if (!ft_strncmp(args[0], "echo", 4) && ft_strlen(args[0]) == 4)
		execute_echo(args + 1);
	else if (!ft_strncmp(args[0], "pwd", 3) && ft_strlen(args[0]) == 3)
		execute_pwd();
	else if (!ft_strncmp(args[0], "env", 3) && ft_strlen(args[0]) == 3)
		print_env_var_list(env_to_char_array(envp_lst));
	else if (!ft_strncmp(args[0], "export", 6) && ft_strlen(args[0]) == 6)
		return (1);
	else if (!ft_strncmp(args[0], "cd", 2) && ft_strlen(args[0]) == 2)
		return (1);
	else if (!ft_strncmp(args[0], "unset", 5) && ft_strlen(args[0]) == 5)
		return (1);
	else if (!ft_strncmp(args[0], "exit", 4) && ft_strlen(args[0]) == 4)
		return (1);
	else
		return (0);
	return (1);
}
