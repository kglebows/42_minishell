/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pharse.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:12:23 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/10 19:31:36 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHARSE_H
# define PHARSE_H

# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

/**
 * @brief Main data structure that holds all information needed for the program.
 * @param exit exit code of main process
 * @param input pointer to minishells input
 */
typedef struct s_dt
{
	int					*exit;
	char				*input;
}						t_dt;

void		ft_error(int code, t_dt *dt);
void		ft_exit(t_dt *dt);
int			*ini_exit(void);
void		exit_code(int code);

#endif