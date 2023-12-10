#include "../../includes/minishell.h"
#include "../../includes/executor.h"

void	ft_close_fd(int fd)
{
	if (fd > STDERR_FILENO)
	{
		printf("about to close fd: %i \n", fd);
		close(fd);
	}
}


void	free_double_char(char **stuff)
{
	int	i;

	i = 0;
	if (stuff && stuff[0] != NULL)
	{
		while (stuff[i] != NULL)
		{
			free (stuff[i]);
			i++;
		}
	}
	free(stuff);
	return ;
}
