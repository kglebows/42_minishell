
#include "minishell.h"

char	*check_env(char *check, int i, t_dt *dt)
{
	t_env			*temp;
	char			*ret;

	temp = dt->envp_lst;
	ret = NULL;
	while (temp)
	{
		if (ft_strncmp(temp->key, check, i) == 0)
		{
			ret = ft_strdup(temp->value);
			break ;
		}
		temp = temp->next;
	}
	return (ret);
}

char	*expand(char q, char *start, t_dt *dt)
{
	int			i;
	char		*temp;
	char		*exp;

	i = 0;
	if (start[i] == '?')
		return (ft_itoa(*ini_exit()));
	while (start[i] == '_' || ft_isalnum(start[i]) == 1)
		i++;
	if (i == 0)
		return(ft_calloc(1, sizeof(char)));
	temp = calloc(i + 1, sizeof(char));
	if (!temp)
		ft_error(-10, dt);
	if (q == '\'')
	{
		ft_strlcpy(temp, &start[-1], i + 2);
		return (temp);
	}
	ft_strlcpy(temp, start, i + 1);
	exp = check_env(temp, i, dt);
	free(temp);
	return (exp);
}

char	*update_string(char* str, char *update)
{
	char		*temp;

	if (update)
		temp = ft_strjoin(str, update);
	else
		temp = ft_strjoin(str, "");
	if (str)
		free(str);
	if (update)
		free(update);
	return (temp);
}

char *ft_expander(char *str, int size, t_dt *dt)
{
	char		q;
	char		*temp;
	int			i;
	char		*c;

	q = ' ';
	i = 0;
	temp = ft_calloc(1, sizeof(char));
	while (i < size)
	{
		if (q == ' ' && (str[i] == '\'' || str[i] == '\"'))
			q = str[i];
		else if ((q == '\'' && str[i] == '\'') || (q == '\"' && str[i] == '\"'))
			q = ' ';
		else if (str[i] == '$')
		{
			temp = update_string(temp, expand(q, &str[i + 1], dt));
			if (str[i + 1] == '?')
				i++;
			else
			{
				while (str[i + 1] == '_' || ft_isalnum(str[i + 1]) == 1)
					i++;
			}
		}
		else
		{
			c = ft_calloc(2, sizeof(char));
			c[0] = str[i];
			c[1] = '\0';
			temp = update_string(temp, c);
		}
		i++;
	}
	if (q != ' ')
		return (NULL);
	return (temp);
}
