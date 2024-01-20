#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <sys/stat.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

// FOR LINUX VALGRIND
// # include <wait.h>
//

# include "../lib/libft/libft.h"

# include "parse.h"
# include "builtin.h"
# include "executor.h"
# include "utils.h"


t_return	ft_parse(t_dt *dt);
t_env	*create_env_var_node(char *str);


# define FALSE 0
# define TRUE 1

#endif
