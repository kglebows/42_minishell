/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:28:42 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/17 18:42:34 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the argument is a valid option for echo
 * @param arg Argument to check
 * @return true if the argument is a valid option, false otherwise
 */
bool	is_valid_option(const char *arg, bool newline)
{
	int	n;

	(void)newline;
	if (arg[0] == '-' && arg[ft_strlen(arg)] == '\0')
	{
		n = 1;
		while (n < ft_strlen(arg))
		{
			if (arg[n] != 'n')
				return (false);
			n++;
		}
		if (n == ft_strlen(arg))
			newline = false;
		return (true);
	}
	return (false);
}

/**
 * @brief Writes a string to STDOUT_FILENO followed by a space if needed
 * @param str String to write
 * @param hasNext True if there is another argument, false otherwise
 */
void	write_with_space(const char *str, bool hasNext)
{
	write(STDOUT_FILENO, str, strlen(str));
	if (hasNext)
		write(STDOUT_FILENO, " ", 1);
}

// /**
//  * @brief Executes the 'echo' command
//  * @param args Command arguments
//  */
// void	execute_echo(char **args)
// {
// 	bool	newline;
// 	int		i;

// 	newline = true;
// 	i = 0;
// 	while (args[i] != NULL)
// 	{
// 		if (is_valid_option(args[i], newline) && !newline)
// 			break ;
// 		else
// 			write_with_space(args[i], args[i + 1] != NULL);
// 		i++;
// 	}
// 	if (newline)
// 		write(STDOUT_FILENO, "\n", 1);
// }

/**
 * @brief Executes the 'echo' command
 * @param args Command arguments
 */
void	execute_echo(char **args)
{
	bool	newline;
	bool	endofn;
	int		i;
	int		n;

	newline = true;
	endofn = false;
	i = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] == '-' && args[i][ft_strlen(args[i])] == '\0'
			&& endofn == false)
		{
			n = 1;
			while (n < ft_strlen(args[i]))
			{
				if (args[i][n] != 'n')
				{
					endofn = true;
					i--;
					break ;
				}
				n++;
			}
			if (n == ft_strlen(args[i]))
				newline = false;
		}
		else
		{
			endofn = true;
			write(STDOUT_FILENO, args[i], strlen(args[i]));
			if (args[i + 1] != NULL)
				write(STDOUT_FILENO, " ", 1);
			else
			{
				i++;
				break ;
			}
		}
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
}
