/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:27:34 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/12 04:02:46 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_many_pipis(t_token_type pipi, t_dt *dt)
{
	t_token		*temp;
	int			i;

	i = 0;
	temp = dt->token;
	while (temp)
	{
		if (temp->type == pipi)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	create_cmdtable(t_dt *dt)
{
	int			i;

	i = how_many_pipis(PIPE, dt);
	dt->cmdtable = (t_cmdtable **)ft_calloc(i + 2, sizeof(t_cmdtable *));
	if (!dt->cmdtable)
		ft_error(-10, dt);
	while (i >= 0)
	{
		dt->cmdtable[i] = ft_calloc(1, sizeof(t_cmdtable));
		if (!dt->cmdtable[i])
			ft_error(-10, dt);
		dt->cmdtable[i]->cmdrow = NULL;
	}
	
}

void	ft_parse(t_dt *dt)
{
	t_token		*temp;

	temp = dt->token;
	if (temp->type == PIPE)
		ft_error(-12, dt);
	while (temp)
	{
		if (temp->type < 5 && !temp->next)
			ft_error(-13, dt);
		if (temp->type < 4 && temp->next->type < 5)
			ft_error(-14, dt);
		temp = temp->next;
	}
}

