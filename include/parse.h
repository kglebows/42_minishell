/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:12:23 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/14 18:45:32 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

/**
 * @brief Type of a token 0-3 Redirection, 4 pipe, 5-7 text
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
 * @brief Redirection information
 * @param type Type of redirection
 * @param data Redirection destination or deliminator for heredoc
 */
typedef struct s_rdr
{
	t_token_type		type;
	char				*data;
}			t_rdr;

// ! //

// notes for Execution :
// the files are created to the point of reaching in-file that does not exist
// heredocs are executed first

// ^ //

/**
 * @brief Command Table for Executor
 * @param cmd Array of command with options
 * @param cmd_nb Number of command elements (cmd + options)
 * @param rdr Array of redirections
 * @param rdr_nb Number of redirections (in and out)
 * @param fd_in input file, default - standard input
 * @param fd_out output file, default - standard output
 */
typedef struct t_cmdtable
{
	char				**cmd;
	int					cmd_nb;
	t_rdr				*rdr;
	int					rdr_nb;
	int					fd_in;
	int					fd_out;
	int					fd;
}			t_cmdtable;

/**
 * @brief Main data structure that holds all information needed for the program.
 * @param exit exit code of main process
 * @param envp ENVironment Pointer. String with environment information.
 * @param input pointer to minishells input
 * @param token linked list of tokens header
 * @param nrofpipes number of pipes
 */
typedef struct s_dt
{
	int					*exit;
	char				**envp;
	char				*input;
	t_token				*token;
	t_cmdtable			**cmdtable;
	int					nrofpipes;
}						t_dt;

void		ft_error(int code, t_dt *dt);
void		ft_exit(t_dt *dt);
int			*ini_exit(void);
void		exit_code(int code);
void		ft_token(t_dt *dt);

/**
 * @brief Tokenization - Turning input into tokens
 * @param dt main data structure
 * @return
*/
void	ft_token(t_dt *dt);

/**
 * @brief Calculate the lenght of string for token
 * @param str Pointer to first character in input for token
 * @param stop Stop character that closes token
 * @param dt main data structure
 * @return lenght of data
*/
int	lenght(char *str, char stop, t_dt *dt);

/**
 * @brief Create a new token and add it at the end of the token list
 * @param type Type of a token
 * @param lenght lenght of data
 * @param data content of input assosiated with token
 * @param dt main data structure
 * @return lenght of data
*/
int	token_ini(t_token_type type, int lenght, char *data, t_dt *dt);


void	fill_cmdtable(t_cmdtable *cmdtable, t_token *token, t_dt *dt);
void print_cmdtable(t_dt *dt);
void	fill_cmd(t_cmdtable *cmdtable, t_token *token, t_dt *dt);
#endif
