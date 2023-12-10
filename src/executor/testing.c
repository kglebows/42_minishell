#include "../../includes/minishell.h"
#include "../../includes/executor.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd_list	*great_list;

	printf("how much is the fish?\n");
	if (argc == 0 || argv[0] == NULL)
		return (1);
	great_list = create_cmd_list("pwd", "pwd", NULL, NULL);
	great_list->next = create_cmd_list2("cat", "cat", great_list, NULL);
	executor(great_list, envp);
	free_cmd_list(great_list->next);
	free_cmd_list(great_list);
	printf("sunshine in the air\n");
	return (0);
}

t_cmd_list	*create_cmd_list(char *cmd, char *builtin, t_cmd_list *prev, t_cmd_list *next)
{
	t_cmd_list	*new_cmd;

	new_cmd = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (new_cmd == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	new_cmd->cmd = (char *)malloc(ft_strlen(cmd) + 1);
	if (new_cmd->cmd == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(new_cmd->cmd, cmd, ft_strlen(cmd));
	new_cmd->builtin = (char *)malloc(ft_strlen(builtin) + 1);
	ft_strlcpy(new_cmd->builtin, builtin, ft_strlen(builtin));
	new_cmd->str = (char **) ft_calloc(10, sizeof(char *));
	new_cmd->str[0] = "pwd";
	new_cmd->str[1] = NULL;
	new_cmd->str[2] = NULL;
	new_cmd->in = STDIN_FILENO;
	new_cmd->out = STDOUT_FILENO;
	new_cmd->redirect_list = NULL; // create_redir_list(infile, "bvb.txt");
	new_cmd->prev = prev;
	new_cmd->next = next;
	return (new_cmd);
}

t_cmd_list	*create_cmd_list2(char *cmd, char *builtin, t_cmd_list *prev, t_cmd_list *next)
{
	t_cmd_list	*new_cmd;

	new_cmd = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (new_cmd == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	new_cmd->cmd = (char *)malloc(ft_strlen(cmd) + 1);
	if (new_cmd->cmd == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(new_cmd->cmd, cmd, ft_strlen(cmd));
	new_cmd->builtin = (char *)malloc(ft_strlen(builtin) + 1);
	ft_strlcpy(new_cmd->builtin, builtin, ft_strlen(builtin));
	new_cmd->str = (char **) ft_calloc(10, sizeof(char *));
	new_cmd->str[0] = "cat";
	new_cmd->str[1] = NULL;
	new_cmd->str[2] = NULL;
	new_cmd->in = STDIN_FILENO;
	new_cmd->out = STDOUT_FILENO;
	new_cmd->redirect_list = create_redir_list(outfile, "test2.txt");
	new_cmd->next = next;
	new_cmd->prev = prev;
	return (new_cmd);
}

/* void	ft_lstadd_node(t_cmd_list *old_lst, t_list *new)
{
		t_cmd_list	*new_list;

		new_list = *create_cmd_list(char *cmd, char *builtin);

} */

t_redir_list	*create_redir_list(t_redirect redir, char *file)
{
	t_redir_list	*new_redirect_list;

	new_redirect_list = (t_redir_list *)malloc(sizeof(t_redir_list));
	new_redirect_list->redirection = redir;
	new_redirect_list->file = (char *)ft_calloc(ft_strlen(file), sizeof(char));
	new_redirect_list->file = file;
	return (new_redirect_list);
}

// Function to free memory allocated for a t_cmd_list
void	free_cmd_list(t_cmd_list *cmd_list)
{
	free(cmd_list->cmd);
	free(cmd_list->builtin);
	free(cmd_list);
}

/* void	ft_print_doublechar(char **double)
{
	int	i;

	i = 0;
	while (double[i] != NULL)
	{
		printf("%s\n", double[i]);
		i++;
	}
}
 */