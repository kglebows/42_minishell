/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:27:34 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/13 14:53:52 by kglebows         ###   ########.fr       */
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
			temp = temp->next;
		else if (temp->type == token)
			i++;
		temp = temp->next;
	}
	return (i);
}

/**
 * @brief Create an command table of height of number of pipes.
 * @param dt main data structure
 * @return 
*/
void	create_cmdtable(t_dt *dt)
{
	int			i;
	t_token		*temp;

	temp = dt->token;
	dt->nrofpipes = how_many(PIPE, temp);
	dt->cmdtable = (t_cmdtable **)ft_calloc(dt->nrofpipes + 2, sizeof(t_cmdtable *));
	if (!dt->cmdtable)
		ft_error(-10, dt);
	i = 0;
	while (temp && i <= dt->nrofpipes)
	{
		fill_cmdtable(dt->cmdtable[i], temp, dt);
		while (temp && temp->type != PIPE)
			temp = temp->next;
		temp = temp->next;
		i++;
	}
}

void	fill_cmd(t_cmdtable *cmdtable, t_token *token, t_dt *dt);
{
	t_token			*temp;
	int				i;
	int				j;

	cmdtable->cmd = (char **) ft_calloc(cmdtable->cmd_nb + 1, sizeof(char *));
	cmdtable->rdr = (t_rdr **) ft_calloc(cmdtable->rdr_nb + 1, sizeof(char *));;
	temp = token;
	while (temp->type != PIPE)
	{
		if (temp->type > 4)
			cmdtable->cmd
		
		temp = temp->next;
	}
}

void	fill_cmdtable(t_cmdtable *cmdtable, t_token *token, t_dt *dt)
{
	cmdtable = ft_calloc(1, sizeof(t_cmdtable));
	if (!cmdtable)
		ft_error(-10, dt);
	cmdtable->cmd_nb = how_many(TEXT, token)
						+ how_many(TEXT_SQUOTE, token)
						+ how_many(TEXT_DQUOTE, token);
	cmdtable->rdr_nb = how_many(REDIRECTION_IN, token)
						+ how_many(REDIRECTION_OUT, token)
						+ how_many(REDIRECTION_IN_HEREDOC, token)
						+ how_many(REDIRECTION_OUT_APPEND, token);
	fill_cmd(cmdtable, token, dt);
	cmdtable->fd_in =
	cmdtable->fd_out =
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

