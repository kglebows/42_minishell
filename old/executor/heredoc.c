#include "minishell.h"

/**
 * @brief	creates a heredoc file
 * @param delimiter The delimiter of the heredoc (f.e. EOF)
 * @return File descriptor to the heredoc file
 */
*/
int	create_heredoc(char *delimiter)
{
	int		fd;
	char	*line;

	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	fd = open("heredoc", O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}
