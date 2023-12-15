/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:26:44 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/15 16:57:35 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes all default values for main data structure.
 * @param argc ARGument Count. Number of input arguments.
 * @param argv ARGument Vector. String holding input arguments.
 * @param envp ENVironment Pointer. String with environment information.
 * @return pointer to main data structure.
*/
t_dt *ini_dt(int argc, char *argv[], char *envp[])
{
	static t_dt		dt;

	if (argc != 1)
		ft_error(-1, &dt);
	(void)argv;
	dt = (t_dt){
		.exit = ini_exit(),
		.envp = envp,
		.envp_lst = init_env_var(envp),
		.input = NULL,
		.token = NULL,
		.fd_in = dup(STDIN_FILENO),
		.fd_out = dup(STDOUT_FILENO),
		.nrofpipes = 0
	};
	return (&dt);
}

t_return check_input(t_dt *dt)
{
	char		*temp;
	int			i;

	i = 0;
	temp = dt->input;
	while (ft_isspace(temp[i]) == 1)
		i++;
	if (temp[i] == '\0')
		return (KO);
	else
		return (OK);
}

/**
 * @brief Minishell loop
 * @param dt main data structure
 * @return
*/
void ini_minishell(t_dt *dt)
{
	while (42)
	{
		init_signal_handler();
		dt->input = readline("Mini$hell ];> ");
		if (!dt->input)
			break ;
		// printf("Wpisany INPUT: %s\n", dt->input);
		if (check_input(dt) == OK)
		{
			add_history(dt->input);
			ft_token(dt);
			// ft_lexer(dt);
			if (ft_parse(dt) == OK)
				ft_executor(dt);
		}
		free(dt->input);
		dt->token = NULL; // Leeks : i need to free token and cmdtable
	}
}

/**
 * @brief Hello World!
 * @param argc ARGument Count. Number of input arguments.
 * @param argv ARGument Vector. String holding input arguments.
 * @param envp ENVironment Pointer. String with environment information.
 * @return Exit code for terminal.
*/
int	main(int argc, char *argv[], char *envp[])
{
	t_dt		*dt;

	dt = ini_dt(argc, argv, envp);
	ini_minishell(dt);
	ft_exit(dt);
	return (*dt->exit);
}
