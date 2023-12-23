
#include "minishell.h"

/**
 * @brief Prepares and executes commands in the minishell
 * @param minishell Pointer to the minishell data structure
 * @return 1 on success
 */
int	prepare_and_execute(t_dt *minishell)
{
	int		i;
	int		table_num;
	bool	last_cmd;
	int		cmd_num;

	cmd_num = minishell->cmdtable[0]->cmd_nb;
	i = 0;
	table_num = 0;
	while (minishell->cmdtable[table_num])
		table_num++;
	if (cmd_num != 0 && table_num == 1
		&& !ft_strncmp(minishell->cmdtable[0]->cmd[0], "exit", 4))
		exit_shell(minishell->cmdtable[0]->cmd);
	while (i < table_num)
	{
		if (cmd_num != 0 && !ft_strncmp(minishell->cmdtable[i]->cmd[0], "exit",
				4))
		{
			i++;
			continue ;
		}
		if (i + 1 == table_num)
			last_cmd = true;
		minishell->cmdtable[i]->fd_rdr_out = 0;
		execute(minishell->cmdtable[i], minishell, last_cmd);
		i++;
	}
	ft_waitpid(minishell, table_num);
	return (1);
}

char	*find_path(t_cmdtable *table, char **env, bool last_cmd)
{
	char	*temp;

	if (access(table->cmd[0], X_OK) == 0)
		temp = table->cmd[0];
	else
		temp = cmd_path(table->cmd[0], env);
	if (!temp)
	{
		if (last_cmd)
			dup2(table->fd_in, STDIN_FILENO);
		exit(127);
	}
	return (temp);
}

char **env_to_char_array(t_env *head) {
    if (head == NULL) {
        return NULL;
    }

    int size = 0;
    t_env *current = head;

    // Count the number of elements in the linked list
    while (current != NULL) {
        size++;
        current = current->next;
    }

    // Allocate memory for the char** array
    char **env_array = (char **)malloc((size + 1) * sizeof(char *));

    if (env_array == NULL) {
        // Memory allocation failure
        return NULL;
    }

    // Copy the linked list elements into the char** array
    current = head;
    int i = 0;

    while (current != NULL) {
        // Calculate the length of the string
        size_t key_len = strlen(current->key);
        size_t value_len = strlen(current->value);
        env_array[i] = (char *)malloc(key_len + value_len + 2); // +2 for '=' and '\0'

        if (env_array[i] == NULL) {
            // Memory allocation failure
            // Cleanup and return NULL
            for (int j = 0; j < i; j++) {
                free(env_array[j]);
            }
            free(env_array);
            return NULL;
        }

        // Copy the key and value into the array element
        strcpy(env_array[i], current->key);
        strcat(env_array[i], "=");
        strcat(env_array[i], current->value);

        i++;
        current = current->next;
    }

    // Set the last element of the array to NULL
    env_array[i] = NULL;

    return env_array;
}
/**
 * @brief Executes a child process for a command table
 * @param table Pointer to the command table
 * @param env Environment variables
 * @param last_cmd Flag indicating if this is the last command in a pipeline
 * @param envp_lst Linked list of environment variables
 */
void	child(t_cmdtable *table, char **env, bool last_cmd, t_env *envp_lst,
		int *fd)
{
	char	*path;

	path = find_path(table, env, last_cmd);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	if (check_redirections(table))
		exit(1);
	else
	{
		if (table->fd_rdr_out)
			dup2(table->fd_rdr_out, STDOUT_FILENO);
		if (last_cmd && !table->fd_rdr_out)
			dup2(table->fd_out, STDOUT_FILENO);
		if (exe_built_in_cmds(table->cmd, env, envp_lst) == 1)
			exit(EXIT_SUCCESS);
		else
			execve(path, table->cmd, env_to_char_array(envp_lst));
	}
}
/**
 * @brief Executes a command table in the minishell
 * @param table Pointer to the command table
 * @param minishell Pointer to the minishell data structure
 * @param last_cmd Flag indicating if this is the last command in a pipeline
 */
void	execute(t_cmdtable *table, t_dt *minishell, bool last_cmd)
{
	int	pid1;
	int	fd[2];

	if (pipe(fd) == -1)
		ft_putstr_fd("Pipe Error\n", 2);
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid1 == 0)
		child(table, minishell->envp, last_cmd, minishell->envp_lst, fd);
	else
	{
		table->fd_rdr_out = 0;
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		if (last_cmd)
			dup2(table->fd_in, STDIN_FILENO);
	}
}
/**
 * @brief Executes built-in commands or external executables
 * @param args Command arguments
 * @param env Environment variables
 * @param envp_lst Linked list of environment variables
 * @return 1 if the command was executed successfully,
	0 if not a built-in command, -1 on error
 */
int	exe_built_in_cmds(char **args, char **env, t_env *envp_lst)
{
	if (!ft_strncmp(args[0], "echo", 4) && ft_strlen(args[0]) == 4)
		execute_echo(args + 1);
	else if (!ft_strncmp(args[0], "pwd", 3) && ft_strlen(args[0]) == 3)
	{
		if (!execute_pwd())
			return (-1);
	}
	else if (!ft_strncmp(args[0], "cd", 2) && ft_strlen(args[0]) == 2)
	{
		if (!execute_cd(args, envp_lst))
			return (-1);
	}
	else if (!ft_strncmp(args[0], "export", 6) && ft_strlen(args[0]) == 6)
	{
		if (args[1] && !set_env(&envp_lst, args[1]))
			return (-1);
	}
	else if (!ft_strncmp(args[0], "unset", 5) && ft_strlen(args[0]) == 5)
	{
		if (args[1])
			unset_env(&envp_lst, args[1]);
	}
	else if (!ft_strncmp(args[0], "env", 3) && ft_strlen(args[0]) == 3)
		print_env_var_list(env);
	else
		return (0);
	return (1);
}
