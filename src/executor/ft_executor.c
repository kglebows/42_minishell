/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:28:29 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/13 19:37:32 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_executor(t_dt *dt)
{
	(void)dt;
	executor(dt->cmdtable[0], dt->envp);
	//This is your entrypoint for executor, have fun xD
}
