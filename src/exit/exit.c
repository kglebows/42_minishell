/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:04:14 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/19 17:27:13 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_all_minishell(void)
{
	FILE *cmd_pipe;
	char buffer[256];
	int pid;

	cmd_pipe = popen("pgrep -x minishell", "r");
	if (cmd_pipe == NULL)
	{
		perror("popen");
		exit(EXIT_FAILURE);
	}
	while (fgets(buffer, sizeof(buffer), cmd_pipe) != NULL)
	{
		pid = ft_atoi(buffer);
		if (pid != getpid())
		{
			if (kill(pid, SIGTERM) == -1)
				perror("kill");
		}
	}
	pclose(cmd_pipe);
}

void exit_shell(char **args, t_dt *minishell)
{
	int exit_code_var;
	int arg_count;

	exit_code_var = 0;
	arg_count = 0;
	while (args[arg_count] != NULL)
		arg_count++;
	if (arg_count == 1)
	{
		close(minishell->fd_out);
		close(minishell->fd_in);
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit_all_minishell();
		exit(exit_code_var);
	}
	if (arg_count == 2)
	{
		if (ft_isdigit(args[1][0]) || (args[1][0] == '-' && ft_isdigit(args[1][1])))
		{
			dup2(minishell->fd_out, STDOUT_FILENO); // close fd_out and in
			close(minishell->fd_out);
			close(minishell->fd_in);
			exit_code_var = atoi(args[1]);
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			exit_all_minishell();
			exit(exit_code_var);
		}
		else
		{
			dup2(minishell->fd_out, STDOUT_FILENO);
			close(minishell->fd_out);
			close(minishell->fd_in);
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
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
		return;
	}
}
