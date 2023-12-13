/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:27:34 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/13 13:52:42 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief How many tokens are there in token list.
 *  If PIPE - counts pipes in whole list.
 *  If TEXT - counts elements for cmd between pipes.
 * 	If REDIRECTION - counts number of redirections between pipes.
 * @param token token to be counted
 * @param start token from which to start the count
 * @return number of pipes or tokens between pipes
*/
int	how_many(t_token_type token, t_token *start)
{
	t_token		*temp;
	int			i;

	i = 0;
	temp = start;
	while (temp && (token == PIPE || temp->type != PIPE))
	{
		if ((token == TEXT || token == TEXT_SQUOTE || token == TEXT_DQUOTE)
			&& temp->type < 4)
			break ;
		if (temp->type == token)
			i++;
		temp = temp->next;
	}
	return (i);
}

/**
 * @brief Create an empty cmd table of height depending on number of pipes
 * @param dt main data structure
 * @return 
*/
void	create_cmdtable(t_dt *dt)
{
	int			i;

	dt->nrofpipes = how_many(PIPE, dt->token);
	dt->cmdtable = (t_cmdtable **)ft_calloc(dt->nrofpipes + 2, sizeof(t_cmdtable *));
	if (!dt->cmdtable)
		ft_error(-10, dt);
	i = 0;
	while (i <= dt->nrofpipes)
	{
		dt->cmdtable[i] = ft_calloc(1, sizeof(t_cmdtable));
		if (!dt->cmdtable[i])
			ft_error(-10, dt);
		dt->cmdtable[i]->cmd_nb = how_many(TEXT, dt->token)
			+ how_many(TEXT_SQUOTE, dt->token) + how_many(TEXT_DQUOTE, dt->token);
		dt->cmdtable[i]->cmd = NULL;
		dt->cmdtable[i]->rdr_nb = how_many(REDIRECTION_IN, dt->token) + how_many()
			+ how_many(TEXT_SQUOTE, dt->token) + how_many(TEXT_DQUOTE, dt->token);
		dt->cmdtable[i]->rdr = 
		dt->cmdtable[i]->fd_in =
		dt->cmdtable[i]->fd_out =
		i++;
	}
}

void	fill_cmdtable(t_dt *dt)
{
	int				y;
	t_token			*temp;

	temp = dt->token;
	y = 0;
	while (temp)
	{
		while (temp && temp->type != PIPE)
		{
			
			y++;
			temp = temp->next;
		}
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
	create_cmdtable(dt);
	
}

