/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:26:44 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/18 19:09:47 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// char *quote_magic(char *str, int size, t_dt *dt)
// {
// 	char			*temp;

// 	temp = calloc(size + 1, sizeof(char));
// 	if (!temp)
// 		ft_error(-10, dt);
// 	ft_strlcpy(temp, str, size + 1);
// 	return (temp);
// }

// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	src_len;

// 	src_len = ft_strlen(src);
// 	if (src_len < dstsize)
// 		ft_memmove(dst, src, src_len + 1);
// 	else if (dstsize > 0)
// 	{
// 		ft_memmove(dst, src, dstsize - 1);
// 		dst[dstsize - 1] = '\0';
// 	}
// 	return (src_len);
// }

char	*check_env(char *check, int i, t_dt *dt)
{
	t_env			*temp;
	char			*ret;

	temp = dt->envp_lst;
	ret = NULL;
	while (temp)
	{
		// printf(":: Checking... %s vs %s\n", check, temp->key);
		if (ft_strncmp(temp->key, check, i) == 0)
		{
			ret = ft_strdup(temp->value);
			break ;
		}
		temp = temp->next;
	}
	return (ret);
}

char	*expand(char q, char *start, t_dt *dt)
{
	int			i;
	char		*temp;
	char		*exp;

	i = 0;
	if (start[i] == '?')
		return (ft_itoa(*ini_exit()));
	while (start[i] == '_' || ft_isalnum(start[i]) == 1)
		i++;
	if (i == 0)
		return(ft_calloc(1, sizeof(char)));
	temp = calloc(i + 1, sizeof(char));
	if (!temp)
		ft_error(-10, dt);
	if (q == '\'')
	{
		ft_strlcpy(temp, &start[-1], i + 2);
		return (temp);
	}
	ft_strlcpy(temp, start, i + 1);
	exp = check_env(temp, i, dt);
	free(temp);
	return (exp);
}

char	*update_string(char* str, char *update)
{
	char		*temp;

	if (update)
		temp = ft_strjoin(str, update);
	else
		temp = ft_strjoin(str, "");
	if (str)
		free(str);
	if (update)
		free(update);
	return (temp);
}

char *ft_expander(char *str, int size, t_dt *dt)
{
	char		q;
	char		*temp;
	int			i;
	// int			k;
	char		*c;

	q = ' ';
	i = 0;
	temp = ft_calloc(1, sizeof(char));
	while (i < size)
	{
		if (q == ' ' && (str[i] == '\'' || str[i] == '\"'))
		{
			q = str[i];
			i++;
		}
		else if ((q == '\'' && str[i] == '\'') || (q == '\"' && str[i] == '\"'))
		{
			q = ' ';
			i++;
		}
		else if (str[i] == '$')
		{
			// printf("<%c>", str[i]);
			i++;
			temp = update_string(temp, expand(q, &str[i], dt));
			if (str[i] == '?')
				i++;
			else
			{
				while (str[i] == '_' || ft_isalnum(str[i]) == 1)
					i++;
			}
		}
		else
		{
			c = ft_calloc(2, sizeof(char));
			c[0] = str[i];
			c[1] = '\0';
			temp = update_string(temp, c);
			i++;
		}
	}
	if (q != ' ')
	{
		// ft_error(-11, dt);
		return (NULL);
	}
	
	return (temp);


		
		// else
		// {
		// 	k = 0;
		// 	while (str[i + k] && str[i + k] != '\'' && str[i + k] != '\"' && str[i + k] != '$' && i + k < size)
		// 	// while (str[i + k]
		// 	// 	&& (str[i + k] != '\'' && q == '\'')
		// 	// 	&& (str[i + k] != '\'' && q == '\'')
		// 	// 	&& (str[i + k] != '\"' && q != '\'')
		// 	// 	&& (str[i + k] != '$')
		// 	// 	&& i + k < size)
		// 		{
		// 			printf("CHECKING: %c\n", str[i + k]);
		// 			k++;
		// 		}
		// 	// // if (k != 0 && (str[i + k] == '\"' || str[i + k] == '\''))
		// 		// temp = update_string(temp, ft_strslice(&str[i], k - 1, dt));
		// 	// if (k != 0 && q != ' ')
		// 	// {
		// 		temp = update_string(temp, ft_strslice(&str[i], k, dt));
		// 		// i++;
		// 	// }
		// 	// if (k != 0 && q == ' ')
		// 	// 	temp = update_string(temp, ft_strslice(&str[i], k, dt));
		// 	// if (k != 0)
		// 		i += k;
		// 	// printf("SIZE: %d :: I: %d\n", size, i);
		// 	// sleep(1);
		// }
}
