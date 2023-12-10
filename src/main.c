#include "minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (argc != 1 || argv[1])
		exit(0);
	shell_init(shell);
	shell_loop(shell, envp);
}

void	shell_init(t_shell *shell)
{
	shell->line = NULL;
	shell->pids = 0;
	shell->list = NULL;
}

void	shell_loop(t_shell *shell, char *envp[])
{
	while (42)
	{
		shell->line = readline("minishell$ ");
		if (!shell->line)
			break ;
		printf("line: %s\n", shell->line);
		if (ft_strlen(shell->line) > 0)
			add_history(shell->line);
		shell->list = parser(shell->line);
		if (shell->list)
			executor(shell->list, envp);
		free(shell->line);
		shell->line = NULL;
	}
}