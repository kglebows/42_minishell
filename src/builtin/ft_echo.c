#include "../../includes/minishell.h"
#include "../../includes/executor.h"


/**
 * @brief	takes a message and prints it to stdout
 * @param	message The message to print
 * @return	EXIT_SUCCESS
 */
int	ft_echo(char *message[])
{
	size_t	i;
	int		newline;

	i = 0;
	newline = 1;
	if (!message)
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	if (message[i] && !ft_strncmp(message[i], "-n", 2))
	{
		newline = 0;
		i++;
	}
	while (message[i])
	{
		printf("%s ", message[i]);
		i++;
	}
	if (newline)
		printf("\n");
	return (EXIT_SUCCESS);
}
