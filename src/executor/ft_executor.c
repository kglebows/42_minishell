/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:28:29 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/15 13:23:33 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_executor(t_dt *dt)
{
	(void)dt;
	// if (!ft_strncmp(dt->cmdtable[0]->cmd[0], "exit", 4))
	// {
	// 	ft_putstr_fd("Exiting MiniShell...", 1);
	// 	exit(0);
	// }
	prepare_and_execute(dt);
}
