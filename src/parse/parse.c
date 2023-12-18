/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:27:34 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/18 21:29:55 by kglebows         ###   ########.fr       */
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
	while (temp && (token == PIPE || temp->type != PIPE))
	{
		if (token > 4 && temp->type < 4)
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
t_return	create_cmdtable(t_dt *dt)
{
	int			i;
	t_token		*temp;

	temp = dt->token;
	dt->nrofpipes = how_many(PIPE, temp);
	dt->cmdtable = (t_cmdtable **)ft_calloc(dt->nrofpipes + 2, sizeof(t_cmdtable *));
	if (!dt->cmdtable)
		return (ft_error(-10, dt));
	i = 0;
	while (temp != NULL && i <= dt->nrofpipes)
	{
		dt->cmdtable[i] = ft_calloc(1, sizeof(t_cmdtable));
		if (!dt->cmdtable[i])
			return (ft_error(-10, dt));
		if (fill_cmdtable(dt->cmdtable[i], temp, dt) != OK)
			return (KO);
		while (temp && temp->type != PIPE)
			temp = temp->next;
		i++;
		if (temp)
			temp = temp->next;
	}
	return (OK);
}

t_return	fill_cmd(t_cmdtable *cmdtable, t_token *token, t_dt *dt)
{
	t_token			*temp;
	int				i;
	int				j;

	cmdtable->cmd = (char **) ft_calloc(cmdtable->cmd_nb + 1, sizeof(char *));
	cmdtable->rdr = (t_rdr *) ft_calloc(cmdtable->rdr_nb + 1, sizeof(t_rdr));
	if (!cmdtable->cmd || !cmdtable->rdr)
		return (ft_error(-10, dt));
	temp = token;
	i = 0;
	j = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type > 4)
		{
			cmdtable->cmd[i] = ft_expander(temp->data, temp->lenght, dt);
			if (cmdtable->cmd[i] == NULL)
				return (ft_error(-11, dt));
			i++;
		}
		else
		{
			cmdtable->rdr[j].type = temp->type;
			temp = temp->next;
			cmdtable->rdr[j].data = ft_expander(temp->data, temp->lenght, dt);
			if (cmdtable->rdr[j].data == NULL)
				return (ft_error(-11, dt));
			j++;
		}
		temp = temp->next;
	}
	return (OK);
}

t_return	fill_cmdtable(t_cmdtable *cmdtable, t_token *token, t_dt *dt)
{
	cmdtable->cmd_nb = how_many(TEXT, token)
						+ how_many(TEXT_SQUOTE, token)
						+ how_many(TEXT_DQUOTE, token);
	cmdtable->rdr_nb = how_many(REDIRECTION_IN, token)
						+ how_many(REDIRECTION_OUT, token)
						+ how_many(REDIRECTION_IN_HEREDOC, token)
						+ how_many(REDIRECTION_OUT_APPEND, token);
	cmdtable->fd_in = dup(STDIN_FILENO);
	cmdtable->fd_out = dup(STDOUT_FILENO);
	if (fill_cmd(cmdtable, token, dt) != OK)
		return (KO);
	return(OK);
}

void print_cmdtable(t_dt *dt)
{
	int			i;
	int			j;

	i = 0;
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

t_return	ft_parse(t_dt *dt)
{
	t_token		*temp;

	temp = dt->token;
	if (temp && temp->type == PIPE)
		return (ft_error(-12, dt));
	while (temp)
	{
		if (temp->type < 5 && !temp->next)
			return (ft_error(-13, dt));
		if (temp->type < 4 && temp->next->type < 5)
			return (ft_error(-14, dt));
		temp = temp->next;
	}
	if (create_cmdtable(dt) != OK)
		return (KO);
	// print_cmdtable(dt);
	return (OK);
}

char	*ft_strgetbetween(const char *start, const char *end)
{
	char	*word;
	size_t	i;
	if ((*start == '\'' && *end == '\'') || (*start == '"' && *end == '"'))
	{
		start++;
		end--;
	}
	word = (char *)malloc((end - start + 2) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (*start && start <= end)
	{
		word[i] = *start;
		start++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

static t_env	*create_env_var_node(char *str)
{
	char	*eq_sign_pos;
	t_env	*node;
	eq_sign_pos = ft_strchr(str, '=');
	if (!eq_sign_pos)
		return (NULL);
	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->key = ft_strgetbetween(str, eq_sign_pos - 1);
	if (!node->key)
		return (free(node), NULL);
	node->value = ft_strdup(eq_sign_pos + 1);
	if (!node->value)
		return (free(node->key), free(node), NULL);
	return (node);
}

void	free_env_var_list(t_env *head)
{
	t_env	*temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

t_env	*init_env_var(char *envp[])
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;
	int		i;
	head = NULL;
	tail = NULL;

	i = 0;
	while (envp[i++] != NULL)
	{
		new_node = create_env_var_node(envp[i - 1]);
		if (new_node == NULL)
			return (free_env_var_list(head), NULL);
		if (tail == NULL)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
	}
	return (head);
}

void	test_print_envlist(t_dt *dt)
{
	t_env			*temp;
	int				u;
	
	u = 1;
	temp = dt->envp_lst;
	printf(":::::::::::::::::: env ::::::::::::::::::::\n");
	while (temp)
	{
		printf("%2d :: %-30s :: %s\n", u, temp->key, temp->value);
		temp = temp->next;
		u++;
	}
	printf(":::::::::::::::::::::::::::::::::::::::::::\n");
}
