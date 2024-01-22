/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:07:34 by kglebows          #+#    #+#             */
/*   Updated: 2024/01/19 17:07:37 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_(int code, t_dt *dt)
{
	(void)dt;
	if (code == -10)
		ft_printf("minishell: Memory allocation failed!\n");
	else if (code == -11)
		ft_printf("minishell: Quotes not closed!\n");
	else if (code == -12)
		ft_printf("minishell: syntax error near unexpected token `|'\n");
	else if (code == -13)
		ft_printf("minishell: syntax error near unexpected token\n");
	else if (code == -14)
		ft_printf("minishell: syntax error near unexpected token\n");
	else if (code == -15)
		ft_printf("Error! \n");
	else if (code == -16)
		ft_printf("Error! \n");
	else if (code == -17)
		ft_printf("Error! \n");
	else if (code == -18)
		ft_printf("Error! \n");
	else if (code == -19)
		ft_printf("Error! \n");
	else
		ft_printf("Error! Unknown error code %d!\n", code);
}

t_ok	ft_error(int code, t_dt *dt)
{
	if (code == -1)
		ft_printf("minishell: Minishell takes no arguments!\n");
	else if (code == -2)
		ft_printf("Error! \n");
	else if (code == -3)
		ft_printf("Error! \n");
	else if (code == -4)
		ft_printf("Error! \n");
	else if (code == -5)
		ft_printf("Error! \n");
	else if (code == -6)
		ft_printf("Error! \n");
	else if (code == -7)
		ft_printf("Error! \n");
	else if (code == -8)
		ft_printf("Error! \n");
	else if (code == -9)
		ft_printf("Error! \n");
	else
		error_(code, dt);
	if (code > -10)
		exit_code(2);
	else
		exit_code(258);
	return (KO);
}
