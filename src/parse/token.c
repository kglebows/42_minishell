/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:18:30 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/12 01:52:38 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_isspace(dt->input[i]))
			i++;
		else if (dt->input[i] == '>' && dt->input[i + 1] == '>')
			i += token_ini(REDIRECTION_OUT_APPEND, 2, &dt->input[i], dt);
		else if (dt->input[i] == '>')
			i += token_ini(REDIRECTION_OUT, 1, &dt->input[i], dt);
		else if (dt->input[i] == '<' && dt->input[i + 1] == '<')
			i += token_ini(REDIRECTION_IN_HEREDOC, 2, &dt->input[i], dt);
		else if (dt->input[i] == '<')
			i += token_ini(REDIRECTION_IN, 1, &dt->input[i], dt);
		else if (dt->input[i] == '|')
			i += token_ini(PIPE, 1, &dt->input[i], dt);
		else if (dt->input[i] == '\'')
			i += token_ini(TEXT_SQUOTE, lenght(&dt->input[i], '\'', dt), &dt->input[i], dt);
		else if (dt->input[i] == '\"')
			i += token_ini(TEXT_DQUOTE, lenght(&dt->input[i], '\"', dt), &dt->input[i], dt);
		else
			i += token_ini(TEXT, lenght(&dt->input[i], ' ', dt), &dt->input[i], dt);
	}
}

/**
 * @brief Calculate the lenght of string for token
 * @param str Pointer to first character in input for token
 * @param stop Stop character that closes token
 * @param dt main data structure
 * @return lenght of data
*/
int	lenght(char *str, char stop, t_dt *dt)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == stop || str[i] == '<' || str[i] == '>')
			break ;
	}
	if (stop == '\'' || stop == '\"')
	{
		if (str[i] == '\0')
			ft_error(-11, dt);
		i++;
		if (str[i] == '\'')
			i += lenght(&str[i], '\'', dt);
		else if (str[i] == '\"')
			i += lenght(&str[i], '\"', dt);
		else if (str[i] != '>' && str[i] != '<' && str[i] != ' ')
			i += lenght(&str[i], ' ', dt);
	}
	return (i);
}

/**
 * @brief Create a new token and add it at the end of the token list
 * @param type Type of a token
 * @param lenght lenght of data
 * @param data content of input assosiated with token
 * @param dt main data structure
 * @return lenght of data
*/
int	token_ini(t_token_type type, int lenght, char *data, t_dt *dt)
{
	t_token	*temp;
	t_token	*last;

	last = dt->token;
	temp = ft_calloc(1, sizeof(t_token));
	if (!temp)
		ft_error(-10, dt);
	temp->data = data;
	temp->lenght = lenght;
	temp->type = type;
	temp->next = NULL;
	while (last)
		last = last->next;
	last = temp;
	// DEBUG 
	write(1, data, lenght);
	ft_printf(" :: %d\n", lenght);
	// DEBUG
	return (lenght);
}
