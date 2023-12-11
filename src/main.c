/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:26:44 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/11 20:11:50 by kglebows         ###   ########.fr       */
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
		.input = NULL,
		.token = NULL
	};
	return (&dt);
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
		dt->input = readline("Mini$hell ];> ");
		if (!dt->input)
			break ;
		if (dt->input[0] != '\0')
			add_history(dt->input);
		ft_token(dt); // lex
		// ft_parse(dt);
		// ft_exe(dt);
		
		// if (dt->input[0] != '\n' && dt->input[0] != '\0')
		// 	printf("%s\n", dt->input);
		
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
