/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:29:04 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/13 17:15:24 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_(int code)
{
	if (code == -10)
		printf("Error! Memory allocation failed!\n");
	else if (code == -11)
		printf("Error! Quotes not closed!\n");
	else if (code == -12)
		printf("Error! U start with a pipe?!\n");
	else if (code == -13)
		printf("Error! U end with this token?!\n");
	else if (code == -14)
		printf("Error! U want to redirect what?!\n");
	else if (code == -15)
		printf("Error! cmdtable creation failed! fix your code!\n");
	else if (code == -16)
		printf("Error! cmdtable smthng wrong with element count!\n");
	else if (code == -17)
		printf("Error! \n");
	else if (code == -18)
		printf("Error! \n");
	else if (code == -19)
		printf("Error! \n");
	else
		printf("Error! Unknown error code %d!\n", code);
}

void	ft_error(int code, t_dt *dt)
{
	if (code == -1)
		printf("Error! Minishell takes no arguments!\n");
	else if (code == -2)
		printf("Error! \n");
	else if (code == -3)
		printf("Error! \n");
	else if (code == -4)
		printf("Error! \n");
	else if (code == -5)
		printf("Error! \n");
	else if (code == -6)
		printf("Error! \n");
	else if (code == -7)
		printf("Error! \n");
	else if (code == -8)
		printf("Error! \n");
	else if (code == -9)
		printf("Error! \n");
	else
		error_(code);
	if (code < -9)
		ft_exit(dt);
	else
		exit(*dt->exit);
}
	