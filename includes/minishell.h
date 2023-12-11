#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "executor.h"
# include "../libft/libft.h"
# include "signal.h"


# define FALSE 0
# define TRUE 1

typedef struct s_shell
{
	char			*readline;
	int				pids;
	s_cmd_list		*cmd_list;

}	t_shell;


typedef struct s_signal_status
{
	int				stop_heredoc;
	int				in_cmd;
	int				in_heredoc;
	int				last_signal_num;
}	t_signal_status;

t_signal_status g_signal_status;


// main.c

#endif