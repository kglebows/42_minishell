/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:04:14 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/18 11:21:51 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_all_minishell(void)
{
	FILE	*cmd_pipe;
	char	buffer[256];
	int		pid;

	cmd_pipe = popen("pgrep -x minishell", "r");
	if (cmd_pipe == NULL)
	{
		perror("popen");
		exit(EXIT_FAILURE);
	}
	while (fgets(buffer, sizeof(buffer), cmd_pipe) != NULL)
	{
		pid = atoi(buffer);
		if (pid != getpid())
		{
			if (kill(pid, SIGTERM) == -1)
				perror("kill");
		}
	}
	pclose(cmd_pipe);
}

void	exit_shell(char **args, t_dt *minishell)
{
	int	exit_code_var;
	int	arg_count;

	exit_code_var = 0;
	arg_count = 0;
	while (args[arg_count] != NULL)
		arg_count++;
	if (arg_count == 1)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit_all_minishell();
		exit(exit_code_var);
	}
	if (arg_count == 2)
	{
		if (ft_isdigit(args[1][0]) || (args[1][0] == '-' && ft_isdigit(args[1][1])))
		{
			dup2(minishell->fd_out, STDOUT_FILENO);
			exit_code_var = atoi(args[1]);
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			exit_all_minishell();
			exit(exit_code_var);
		}
		else
		{
			dup2(minishell->fd_out, STDOUT_FILENO);
			ft_putstr_fd("exit: ", STDOUT_FILENO);
			ft_putstr_fd(args[1], STDOUT_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDOUT_FILENO);
			exit_all_minishell();
			exit(255);
		}
	}
	if (arg_count > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		exit_code(1);
		return ;
	}
}
/**
 * @brief Creates static variable for exit code
 * @param -
 * @return adress of current Exit Code for terminal.
 */
int	*ini_exit(void)
{
	static int	exit = 0;

	return (&exit);
}

/**
 * @brief Changes programs exit code
 * @param code new exit code
 * @return
 */
void	exit_code(int code)
{
	int	*exit;

	// printf("minishell : %d: command not found\n", code);
	exit = ini_exit();
	*exit = code;
	// printf("setting exit code :: %d\n", *exit);
}

/**
 * @brief An exit structure
 * @param dt Main program data structure
 * @return
 */
void	ft_exit(t_dt *dt)
{
	exit(*dt->exit);
}
