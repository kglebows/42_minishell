/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:04:14 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/20 10:35:51 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates static variable for exit code
 * @param -
 * @return adress of current Exit Code for terminal.
 */
int	*ini_exit(void)
{
	static int	exit;

	exit = 0;
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
