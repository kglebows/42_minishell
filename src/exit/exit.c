
#include "minishell.h"
void	exit_shell(char **args)
{
	int	exit_code;
	int	arg_count;

	exit_code = 0;
	arg_count = 0;
	while (args[arg_count] != NULL)
	{
		arg_count++;
	}
	if (arg_count == 1)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(exit_code);
	}
	if (arg_count == 2)
	{
		if (isdigit(args[1][0]) || (args[1][0] == '-' && isdigit(args[1][1])))
		{
			exit_code = atoi(args[1]);
			ft_putstr_fd("exit\n", STDERR_FILENO);
			exit(exit_code);
		}
		else
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit(255);
		}
	}
	if (arg_count > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return ;
	}
}
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
