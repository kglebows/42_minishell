/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:45:55 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/16 18:45:30 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

int	ft_strlen_nl(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != 0 && s[i] != '\n')
		i++;
	return (i);
}

// #include <stdio.h>

// int main()
// {
//     int result;
//     char *str = "sdsfeafeesfs";

//     result = ft_strlen(str);
//     printf("%d", result);
//     return(result);  
// }