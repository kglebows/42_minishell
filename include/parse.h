/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:12:23 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/11 20:04:03 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

/**
 * @brief Type of a token
 * @param REDIRECTION_IN <
 * @param REDIRECTION_IN_HEREDOC <<
 * @param REDIRECTION_OUT >
 * @param REDIRECTION_OUT_APPEND >>
 * @param PIPE |
 * @param TEXT ...
 * @param TEXT_SQUOTE '...'
 * @param TEST_DQUOTE  "..."
 */
typedef enum e_token_type
{
	REDIRECTION_IN,
	REDIRECTION_IN_HEREDOC,
	REDIRECTION_OUT,
	REDIRECTION_OUT_APPEND,
	PIPE,
	TEXT,
	TEXT_SQUOTE,
	TEXT_DQUOTE
}				t_token_type;

/**
 * @brief Token list structure
 * @param type Type of a token
 * @param data content of input assosiated with token
 * @param lenght lenght of data
 * @param next pointer to next node, NULL = end of list
 */
typedef struct s_token
{
	t_token_type		type;
	char				*data;
	int					lenght;
	struct s_token		*next;
}			t_token;

/**
 * @brief Main data structure that holds all information needed for the program.
 * @param exit exit code of main process
 * @param envp ENVironment Pointer. String with environment information.
 * @param input pointer to minishells input
 * @param token linked list of tokens header
 */
typedef struct s_dt
{
	int					*exit;
	char				**envp;
	char				*input;
	t_token				*token;
}						t_dt;

void		ft_error(int code, t_dt *dt);
void		ft_exit(t_dt *dt);
int			*ini_exit(void);
void		exit_code(int code);
void		ft_token(t_dt *dt);

#endif