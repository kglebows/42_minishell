#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
typedef struct s_cmd_list	t_cmd_list;

/*enum e_redirect

	piping		|
	infile		<
	outfile		>
	here_doc	<<
	append		>>
*/
typedef enum e_redirect
{
	piping,
	infile,
	outfile,
	here_doc,
	append,
}							t_redirect;

typedef struct s_redir_list
{
	t_redirect				redirection;
	char					*file;
	struct s_redir_list		*next;
	struct s_redir_list		*prev;
}							t_redir_list;

typedef struct s_cmd_list
{
	char					**str;
	char					*cmd;
	char					*builtin;
	int						in;
	int						out;
	struct s_redir_list		*redirect_list;
	struct s_cmd_list		*next;
	struct s_cmd_list		*prev;
}							t_cmd_list;

// exe.c
int							prepare_and_execute(t_dt *minishell);
int							exe_built_in_cmds(char **args, char **env,
								t_env *envp_lst);
void						execute(t_cmdtable *table, t_dt *minishell,
								bool last_cmd);
int							ft_open(char *file, t_token_type rdr_type);
char						*ft_strgetbetween(const char *start,
								const char *end);

// redirector.c
int							check_redirections(t_cmdtable *table);

// builtin.c
void						execute_echo(char **args);
int							execute_cd(char **args, t_env *envp_list);
int							execute_pwd(void);
void						print_env_var_list(char **env);
int							set_env(t_env **head, char *key_val_str);
int							unset_env(t_env **head, char *var);

// exe_utils.c
void						ft_waitpid(t_dt *minishell, int nb_cmd);
char						*get_env(char **env, const char *name);
char						*cmd_path(char *cmd, char **env);

// utils.c
void						free_arrayofstrings(char **array);


// executor_utils.c
int							cmd_is_builtin(char *cmd);
void						free_double_char(char **stuff);
void						ft_close_fd(int fd);


void						free_cmd_list(t_cmd_list *cmd_list);

// builtin.c
int							execute_builtin(t_cmdtable *list, char *envp[]);
int							cmd_is_builtin(char *cmd);
int							ft_echo(char *message[]);
int							ft_env(t_cmdtable *list, char *envp[]);
int							ft_unsetenv(char *str, char *envp[]);


#endif
