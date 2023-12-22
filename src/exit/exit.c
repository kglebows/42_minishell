
#include "minishell.h"

/**
 * @brief Creates static variable for exit code
 * @param -
 * @return adress of current Exit Code for terminal.
*/
int	*ini_exit(void)
{
	static int	exit = 0;

	return (&exit);
}

/**
 * @brief Changes programs exit code
 * @param code new exit code
 * @return 
*/
void	exit_code(int code)
{
	int	*exit;

	exit = ini_exit();
	*exit = code;
}

/**
 * @brief An exit structure
 * @param dt Main program data structure
 * @return 
*/
void	ft_exit(t_dt *dt)
{
	exit(*dt->exit);
}
