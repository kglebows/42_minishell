#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <sys/stat.h>
# include <termios.h>

# include "../lib/libft/libft.h"

# include "parse.h"
// # include "builtin.h"
# include "executor.h"


# define FALSE 0
# define TRUE 1

#endif