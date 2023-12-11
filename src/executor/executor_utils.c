#include "../../includes/minishell.h"
#include "../../includes/executor.h"



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
