/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:06:09 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/10 19:24:41 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pharse.h"

/**
 * @brief Creates static variable for exit code
 * @param -
 * @return Exit code for terminal.
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

	exit = ini_exit();
	*exit = code;
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
