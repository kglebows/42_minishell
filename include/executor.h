#ifndef EXECUTOR_H
# define EXECUTOR_H

// # include "minishell.h"
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
}	t_redirect;

typedef struct s_redir_list
{
	t_redirect			redirection;
	char				*file;
	struct s_redir_list	*next;
	struct s_redir_list	*prev;
}	t_redir_list;

typedef struct s_cmd_list
{
	char				**str;
	char				*cmd;
	char				*builtin;
	int					in;
	int					out;
	struct s_redir_list	*redirect_list;
	struct s_cmd_list	*next;
	struct s_cmd_list	*prev;
}	t_cmd_list;

//executor.c
void		executor(t_cmd_list *list, char *envp[]);

//duping.c
void		dup_output(int outpipe, t_cmd_list *list);
void		dup_input(int inpipe, t_cmd_list *list);
void		close_all_fds(int fd1, int fd2, int fd3);

//pathfinder.c
char		*find_cmd_path(char *envp[], char *argv);
char		**find_path2(char *envp[]);

//executor_utils.c
int			cmd_is_builtin(char *cmd);
void		free_double_char(char **stuff);
void		ft_close_fd(int fd);

//heredoc.c
int			create_heredoc(t_cmd_list *list, char *delimiter);

//redirector.c
void		check_redirections(t_cmd_list *list);
int			set_outfile(t_cmd_list *list);
int			set_infile(t_cmd_list *list);
int			append_file(char *file);

//testing.c
t_cmd_list	*create_cmd_list(char *cmd, char *builtin, t_cmd_list *prev, t_cmd_list *next);
t_cmd_list	*create_cmd_list2(char *cmd, char *builtin, t_cmd_list *prev, t_cmd_list *next);
t_redir_list	*create_redir_list(t_redirect redir, char *file);
void		free_cmd_list(t_cmd_list *cmd_list);

//void		ft_print_doublechar(char **double);

//builtin.c
int	execute_builtin(t_cmd_list *list, char *envp[]);
int	cmd_is_builtin(char *cmd);
int	ft_echo(char *message[]);
int	ft_env(t_cmd_list *list, char *envp[]);
int	ft_exit_changename(t_cmd_list *list);
int	ft_export(t_cmd_list *list, char *envp[]);
int	ft_pwd(t_cmd_list *list, char *envp[]);
int	ft_unset(t_cmd_list *list, char *envp[]);
int	ft_unsetenv(char *str, char *envp[]);

#endif