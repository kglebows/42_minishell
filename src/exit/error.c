
#include "minishell.h"

void	error_(int code)
{
	if (code == -10)
		printf("minishell: Memory allocation failed!\n");
	else if (code == -11)
		printf("minishell: Quotes not closed!\n");
	else if (code == -12)
		printf("minishell: U start with a pipe?!\n");
	else if (code == -13)
		printf("minishell: U end with this token?!\n");
	else if (code == -14)
		printf("minishell: U want to redirect what?!\n");
	else if (code == -15)
		printf("Error! \n");
	else if (code == -16)
		printf("Error! \n");
	else if (code == -17)
		printf("Error! \n");
	else if (code == -18)
		printf("Error! \n");
	else if (code == -19)
		printf("Error! \n");
	else
		printf("Error! Unknown error code %d!\n", code);
}

t_return	ft_error(int code, t_dt *dt)
{
	if (code == -1)
		printf("minishell: Minishell takes no arguments!\n");
	else if (code == -2)
		printf("Error! \n");
	else if (code == -3)
		printf("Error! \n");
	else if (code == -4)
		printf("Error! \n");
	else if (code == -5)
		printf("Error! \n");
	else if (code == -6)
		printf("Error! \n");
	else if (code == -7)
		printf("Error! \n");
	else if (code == -8)
		printf("Error! \n");
	else if (code == -9)
		printf("Error! \n");
	else
		error_(code);
	(void)dt;
	exit_code(2);
	return (KO);
}
	