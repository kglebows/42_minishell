
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
		if (str[i] == stop || str[i] == '<' || str[i] == '>' || str[i] == '|')
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

	temp = ft_calloc(1, sizeof(t_token));
	if (!temp)
		ft_error(-10, dt);
	temp->data = data;
	temp->lenght = lenght;
	temp->type = type;
	temp->next = NULL;
	if (!dt->token)
		dt->token = temp;
	else
	{
		last = dt->token;
		while (last->next)
			last = last->next;
		last->next = temp;
	}
	// DEBUG 
	// write(1, data, lenght);
	// ft_printf(" type:%d len:%d\n", type, lenght);
	// DEBUG
	return (lenght);
}

void	free_token(t_dt *dt)
{
	t_token		*temp;
	t_token		*f_temp;

	temp = dt->token;
	while (temp)
	{
		f_temp = temp;
		temp = temp->next;
		if (f_temp)
			free(f_temp);
	}
	dt->token = NULL;
}
