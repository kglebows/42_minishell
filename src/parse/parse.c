/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:27:34 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/13 19:03:18 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief How many tokens are ther`e in token list.
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
	// printf("Token %d being calculated: \n", temp->type);
	while (temp && (token == PIPE || temp->type != PIPE))
	{
		if (token > 4 && temp->type < 4)
			temp = temp->next;
		else if (temp->type == token)
			i++;
		temp = temp->next;
	}
	// printf("for token %d, starting from %s -> cnt is: %d\n", token, start->data, i);
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
	// printf("typ pierwszego tokena to : %d input to : %s\n", temp->type, temp->data);
	dt->nrofpipes = how_many(PIPE, temp);
	// printf("there are %d pies!\n", dt->nrofpipes);
	dt->cmdtable = (t_cmdtable **)ft_calloc(dt->nrofpipes + 2, sizeof(t_cmdtable *));
	if (!dt->cmdtable)
		ft_error(-10, dt);
	i = 0;
	while (temp != NULL && i <= dt->nrofpipes)
	{
		// printf("creating pipe nr %d ...\n", i);
		dt->cmdtable[i] = ft_calloc(1, sizeof(t_cmdtable));
		if (!dt->cmdtable[i])
			ft_error(-10, dt);
		fill_cmdtable(dt->cmdtable[i], temp, dt);
		while (temp && temp->type != PIPE)
			temp = temp->next;
		i++;
		if (temp)
			temp = temp->next;
	}
}

char *ft_strslice(char *str, int size, t_dt *dt)
{
	char			*temp;

	temp = calloc(size + 1, sizeof(char));
	if (!temp)
		ft_error(-10, dt);
	ft_strlcpy(temp, str, size + 1);
	return (temp);
}


void	fill_cmd(t_cmdtable *cmdtable, t_token *token, t_dt *dt)
{
	t_token			*temp;
	int				i;
	int				j;

	cmdtable->cmd = (char **) ft_calloc(cmdtable->cmd_nb + 1, sizeof(char *));
	cmdtable->rdr = (t_rdr *) ft_calloc(cmdtable->rdr_nb + 1, sizeof(t_rdr));
	if (!cmdtable->cmd || !cmdtable->rdr)
		ft_error(-10, dt);
	temp = token;
	i = 0;
	j = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type > 4)
		{
			cmdtable->cmd[i] = ft_strslice(temp->data, temp->lenght, dt);
			i++;
		}
		else
		{
			cmdtable->rdr[j].type = temp->type;
			temp = temp->next;
			if (temp->type < 5)
				ft_error(-16, dt);
			cmdtable->rdr[j].data = ft_strslice(temp->data, temp->lenght, dt);
			j++;
		}
		temp = temp->next;
		if (i > cmdtable->cmd_nb || j > cmdtable->rdr_nb)
			ft_error(-15, dt);
	}
}

void	fill_cmdtable(t_cmdtable *cmdtable, t_token *token, t_dt *dt)
{
	// cmdtable = ft_calloc(1, sizeof(t_cmdtable));
	// if (!cmdtable)
	// 	ft_error(-10, dt);
	// t_token *temp;
	// temp = dt->token;
	// while (temp)
	// {
	// 	printf("token : %d,len : %d ,starts with : %s\n", temp->type, temp->lenght, temp->data);
	// 	temp = temp->next;
	// }
	
	cmdtable->cmd_nb = how_many(TEXT, token)
						+ how_many(TEXT_SQUOTE, token)
						+ how_many(TEXT_DQUOTE, token);
	cmdtable->rdr_nb = how_many(REDIRECTION_IN, token)
						+ how_many(REDIRECTION_OUT, token)
						+ how_many(REDIRECTION_IN_HEREDOC, token)
						+ how_many(REDIRECTION_OUT_APPEND, token);
	fill_cmd(cmdtable, token, dt);
	cmdtable->fd_in = dup(STDIN_FILENO);
	cmdtable->fd_out = dup(STDOUT_FILENO);
}

void print_cmdtable(t_dt *dt)
{
	int			i;
	int			j;

	i = 0;
	// if (dt->cmdtable[i])
	// 	printf("ZJEBAO SIE COS KURWA \n");
	printf("\n::::: CMD TABLE :::::\n");
	while (i <= dt->nrofpipes)
	{
		printf("  PIPE SPACE %d\n%d	CMD : ", i, dt->cmdtable[i]->cmd_nb);
		j = 0;
		while (dt->cmdtable[i] && j < dt->cmdtable[i]->cmd_nb)
		{
			printf("%s ", dt->cmdtable[i]->cmd[j]);
			j++;
		}
		printf("\n%d	RDR : ", dt->cmdtable[i]->rdr_nb);
		j = 0;
		while (dt->cmdtable[i] && j < dt->cmdtable[i]->rdr_nb)
		{
			printf("%d:%s ", dt->cmdtable[i]->rdr[j].type, dt->cmdtable[i]->rdr[j].data);
			j++;
		}
		printf("\n");
		i++;
	}
	printf(":::::::::::::::::::::\n\n");
}

void	ft_parse(t_dt *dt)
{
	t_token		*temp;

	temp = dt->token;
	if (temp && temp->type == PIPE)
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
	print_cmdtable(dt);
}

