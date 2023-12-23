#include "minishell.h"

/**
 * @brief Adds or Changes a value in Envp list. if key exists, frees memory of key parameter.
 * @param key pointer to allocated string with key
 * @param value pointer to allocated string with value
 * @param dt main data structure
 * @return KO if creation of new node failed or key is NULL
*/
t_return	envp_add_or_change(char *key, char *value ,t_dt *dt)
{
	t_env		*temp;
	t_env		*last;

	if (!key)
		return (KO);
	temp = dt->envp_lst;
	while (temp)
	{
		if (ft_strncmp(key, temp->key, ft_strlen(key)) == 0
			&& ft_strlen(key) == ft_strlen(temp->key))
			break ;
		last = temp;
		temp = temp->next;
	}
	if (temp)
	{
		free(key);
		free(temp->value);
		temp->value = value;
		return (OK);
	}
	last->next = ft_calloc(1, sizeof(t_env));
	if (!last->next)
		return(ft_error(-10, dt));
	last->next->key = key;
	last->next->value = value;
	last->next->next = NULL;
	return (OK);
}

/**
 * @brief Removes an entry of key, if no key found - does nothing.Frees input key.
 * @param key pointer to allocated string with key
 * @param dt main data structure
 * @return KO if key NULL or missing, OK if entry deleted.
*/
t_return	envp_delete(char *key, t_dt *dt)
{
	t_env		*temp;
	t_env		*last;

	if (!key)
		return (KO);
	temp = dt->envp_lst;
	while (temp)
	{
		if (ft_strncmp(key, temp->key, ft_strlen(key)) == 0
			&& ft_strlen(key) == ft_strlen(temp->key))
			break ;
		last = temp;
		temp = temp->next;
	}
	if (temp)
	{
		last->next = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		free(key);
		return (OK);
	}
	free(key);
	return (KO);
}

/**
 * @brief Prints envp list for export command. it shows all declared variables, even those without value
 * @param dt main data structure
*/
void	envp_print_export(t_dt *dt)
{
	t_env			*temp;

	temp = dt->envp_lst;
	while (temp)
	{
		ft_printf("declare -x %s", temp->key);
		if (temp->value)
			ft_printf("=\"%s\"\n", temp->value);
		else
			ft_printf("\n");
		temp = temp->next;
	}
}
/**
 * @brief Prints envp list for env command. it shows only entries that have value
 * @param dt main data structure
*/
void	envp_print_env(t_dt *dt)
{
	t_env			*temp;

	temp = dt->envp_lst;
	while (temp)
	{
		if (temp->value)
			ft_printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

/*
	env, unset and export implementation :
		env
			run	env_print_env(dt);
		unset
			run	envp_delete(NULL, dt);
		unset key
			run	envp_delete(key, dt);
		unset key1 key2 key3 ... 
			run	envp_delete(key1, dt);
			run	envp_delete(key2, dt);
			run	envp_delete(key3, dt);
		export
			run	env_print_export(dt);
		export key || export key=value
			allocate memory for key
			allocate memory for value (if value != NULL)
			run	envp_add_or_change(key, value , dt);
		export key1 key2=value2 key3 ...
			repeat {export key || export key=value} for every argument
*/
