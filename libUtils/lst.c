/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:41:14 by abosc             #+#    #+#             */
/*   Updated: 2025/06/15 05:33:09 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_lstargssize(t_args *lst)
{
	int		i;
	t_args	*tmp;

	i = 0;
	tmp = lst;
	if (!lst)
		return (0);
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char    **ft_tabdup(char **tab)
{
    char    **res;
    int        i;

    i = 0;
    if (!tab)
        return (NULL);
    while (tab[i])
        i++;
    res = malloc((i + 1) * sizeof(char *));
    i = 0;
    while (tab != NULL && tab[i] != NULL)
    {
        i[res] = ft_strdup(tab[i]);
        i++;
    }
    res[i] = NULL;
    return (res);
}

char	*remove_quotes(char *str, int quote_type)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	if (!str || quote_type == NO_Q)
		return (ft_strdup(str));

	len = ft_strlen(str);
	if (len < 2)
		return (ft_strdup(str));

	// Pour les quotes simples complètes, enlever juste les quotes extérieures
	if (quote_type == S_Q && str[0] == '\'' && str[len - 1] == '\'')
	{
		result = malloc(sizeof(char) * (len - 1));
		if (!result)
			return (NULL);
		i = 1;
		j = 0;
		while (i < len - 1)
			result[j++] = str[i++];
		result[j] = '\0';
		return (result);
	}

	// Pour les guillemets doubles simples, enlever juste les quotes extérieures
	if (quote_type == D_Q && str[0] == '\"' && str[len - 1] == '\"')
	{
		result = malloc(sizeof(char) * (len - 1));
		if (!result)
			return (NULL);
		i = 1;
		j = 0;
		while (i < len - 1)
			result[j++] = str[i++];
		result[j] = '\0';
		return (result);
	}

	// Pour les cas complexes, utiliser le processeur de quotes complexes
	return (process_complex_quotes(str));
}

char	*process_complex_quotes(char *str)
{
	char	*result;
	int		i, j;
	int		len;
	int		in_dquote;
	int		in_squote;

	if (!str)
		return (NULL);

	len = ft_strlen(str);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);

	i = 0;
	j = 0;
	in_dquote = 0;
	in_squote = 0;

	while (i < len)
	{
		if (str[i] == '\"' && !in_squote)
		{
			in_dquote = !in_dquote;
			// Ne pas copier les guillemets dans le résultat final
		}
		else if (str[i] == '\'' && !in_dquote)
		{
			in_squote = !in_squote;
			// Ne pas copier les apostrophes dans le résultat final
		}
		else
		{
			// Copier le caractère
			result[j++] = str[i];
		}
		i++;
	}

	result[j] = '\0';
	return (result);
}

void	converter(t_exec *dat_tmp, t_args *tmp, t_mnours *mini, int i)
{
	char	*expanded_name;
	char	*quoted_removed;

	i = 0;
	tmp = dat_tmp->args;
	while (tmp)
	{
		if (tmp->tok == CMD)
			i++;
		tmp = tmp->next;
	}
	dat_tmp->lst = malloc(sizeof(char *) * (i + 1));
	if (!dat_tmp->lst)
		ft_error("malloc error", mini);
	i = 0;
	tmp = dat_tmp->args;
	while (tmp)
	{
		if (tmp->tok == CMD)
		{
			if (tmp->quote != S_Q)
			{
				expanded_name = replace_variable(tmp->name, mini->env, 0);
				if (!expanded_name)
					expanded_name = ft_strdup(tmp->name);
			}
			else
			{
				expanded_name = ft_strdup(tmp->name);
			}
			if (tmp->quote == NO_Q && (ft_strchr(expanded_name, '\'') || ft_strchr(expanded_name, '\"')))
			{
				quoted_removed = process_complex_quotes(expanded_name);
			}
			else
			{
				quoted_removed = remove_quotes(expanded_name, tmp->quote);
			}
			if (!quoted_removed)
				quoted_removed = ft_strdup(expanded_name);
			dat_tmp->lst[i++] = quoted_removed;
			free(expanded_name);
		}
		tmp = tmp->next;
	}
	dat_tmp->lst[i] = NULL;
}

void	ft_lstconvert(t_mnours *mini, t_exec *data)
{
	t_exec	*dat_tmp;
	t_args	*tmp;
	int		i;

	dat_tmp = data;
	while (dat_tmp)
	{
		i = 0;
		tmp = dat_tmp->args;
		converter(dat_tmp, tmp, mini, i);
		dat_tmp = dat_tmp->next;
	}
}

int	ft_envsize(t_env *env)
{
	t_env *tmp;
	int i;

	i = 0;
	tmp = env;
	while(tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**convert_env(t_mnours *mnours)
{
	char **env_tab;
	t_env *tmp;
	int i;
	int	j;
	int k;

	if(mnours->lst_env)
		free_array(mnours->lst_env);
	i = 0;
	tmp = mnours->env;
	env_tab = ft_calloc(sizeof(char *), ft_envsize(mnours->env) + 1);
	while (tmp)
	{
		env_tab[i] = ft_calloc(1, ft_strlen(tmp->name) + ft_strlen(tmp->value) + 2);
		j = ft_strlcpy(env_tab[i], tmp->name, ft_strlen(tmp->name) + 1);
		env_tab[i][j++] = '=';
		k = 0;
		while (tmp->value[k])
			env_tab[i][j++] = tmp->value[k++];
		env_tab[i][j] = '\0';
		tmp = tmp->next;
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}
