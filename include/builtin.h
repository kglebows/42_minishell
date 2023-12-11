#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int		ft_echo(char *message[]);
int		ft_env(t_cmd_list *list, char *envp[]);
int		ft_exit_changename(t_cmd_list *list);
int		ft_export(t_cmd_list *list, char *envp[]);
int		ft_pwd(t_cmd_list *list, char *envp[]);
int		ft_unset(t_cmd_list *list, char *envp[]);
int		ft_unsetenv(char *str, char *envp[]);

char	*get_path(t_cmd_list *list, char *envp[]);
void	update_envp(char *envp[], char *variable, char *value);
void	ft_cd(t_cmd_list *list, char *envp[]);

#endif