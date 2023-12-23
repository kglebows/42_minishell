
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
}					t_token_type;

typedef enum e_return
{
	OK,
	KO
} t_return ;

/**
 * @brief Token list structure
 * @param type Type of a token
 * @param data content of input assosiated with token
 * @param lenght lenght of data
 * @param next pointer to next node, NULL = end of list
 */
typedef struct s_token
{
	t_token_type	type;
	char			*data;
	int				lenght;
	struct s_token	*next;
}					t_token;

/**
 * @brief Redirection information
 * @param type Type of redirection
 * @param data Redirection destination or deliminator for heredoc
 */
typedef struct s_rdr
{
	t_token_type	type;
	char			*data;
}					t_rdr;

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
	char			**cmd;
	int				cmd_nb;
	t_rdr			*rdr;
	int				rdr_nb;
	int				fd_in;
	int				fd_out;
	int				fd_rdr_in;
	int				fd_rdr_out;
}					t_cmdtable;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

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
	int				*exit;
	char			**envp;
	t_env			*envp_lst;
	char			*input;
	t_token			*token;
	t_cmdtable		**cmdtable;
	int				nrofpipes;
	int				fd_in;
	int				fd_out;
}					t_dt;

t_return			(ft_error(int code, t_dt *dt));
void				ft_exit(t_dt *dt);
int					*ini_exit(void);
void				exit_code(int code);
void				exit_shell(char **args);
void				ft_token(t_dt *dt);

/**
 * @brief Tokenization - Turning input into tokens
 * @param dt main data structure
 * @return
 */
void				ft_token(t_dt *dt);

/**
 * @brief Calculate the lenght of string for token
 * @param str Pointer to first character in input for token
 * @param stop Stop character that closes token
 * @param dt main data structure
 * @return lenght of data
 */
int					lenght(char *str, char stop, t_dt *dt);

/**
 * @brief Create a new token and add it at the end of the token list
 * @param type Type of a token
 * @param lenght lenght of data
 * @param data content of input assosiated with token
 * @param dt main data structure
 * @return lenght of data
 */
int					token_ini(t_token_type type, int lenght, char *data,
						t_dt *dt);
void				free_token(t_dt *dt);

t_env				*init_env_var(char *envp[]);

t_return(fill_cmdtable(t_cmdtable *cmdtable, t_token *token, t_dt *dt));
void				print_cmdtable(t_dt *dt);
t_return(fill_cmd(t_cmdtable *cmdtable, t_token *token, t_dt *dt));
void				free_cmdtable(t_dt *dt);

char				*ft_expander(char *str, int size, t_dt *dt);

/*
	TESTING
*/
void				test_print_envlist(t_dt *dt);

/*
env
*/
t_return	envp_add_or_change(char *key, char *value ,t_dt *dt);
t_return	envp_delete(char *key, t_dt *dt);
void		envp_print_export(t_dt *dt);
void		envp_print_env(t_dt *dt);

#endif
