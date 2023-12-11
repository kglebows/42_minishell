/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:18:30 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/11 19:50:16 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Tokenization - Turning input into tokens
 * @param dt main data structure
 * @return 
*/
void	ft_token(t_dt *dt)
{
	int			i;

	i = 0;
	while (dt->input[i] != '\0')
	{
		if(dt->input[i])
		i++;
	}
}


/*
Plan:
1. dojebac libft przez submodule
2. zrobic tokenizacje 
3. 
*/