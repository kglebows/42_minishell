#include "minishell.h"

/**
 * @brief Frees memory allocated for an array of strings
 * @param array Array of strings
 */
void	free_arrayofstrings(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
