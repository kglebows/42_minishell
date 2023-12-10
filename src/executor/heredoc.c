#include "../../includes/minishell.h"
#include "../../includes/executor.h"

int	create_heredoc(t_cmd_list *list, char *delimiter)
{
	int		fd;
	char	*line;

	if(!list)
		return (-1);
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

