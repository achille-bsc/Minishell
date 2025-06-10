/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:41:14 by abosc             #+#    #+#             */
/*   Updated: 2025/06/10 21:46:07 by abosc            ###   ########.fr       */
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

void	free_lst(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
		free(lst[i++]);
	free(lst);
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
	if ((quote_type == S_Q && str[0] == '\'' && str[len - 1] == '\'')
		|| (quote_type == D_Q && str[0] == '\"' && str[len - 1] == '\"'))
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
	return (ft_strdup(str));
}

void	converter(t_exec *dat_tmp, t_args *tmp, t_mnours *mini, int i)
{
	char	*expanded_name;
	char	*quoted_removed;

	while (dat_tmp)
	{
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
				// Appliquer l'expansion des variables d'environnement AVANT de supprimer les guillemets
				// mais seulement si ce ne sont pas des guillemets simples
				if (tmp->quote != S_Q)
				// Pas d'expansion avec les guillemets simples
				{
					expanded_name = replace_variable(tmp->name, mini->env);
					if (!expanded_name)
						expanded_name = ft_strdup(tmp->name);
					// Fallback si échec
				}
				else
				{
					expanded_name = ft_strdup(tmp->name);
				}
				quoted_removed = remove_quotes(expanded_name, tmp->quote);
				dat_tmp->lst[i++] = quoted_removed;
				// Libérer la mémoire allouée
				free(expanded_name);
			}
			tmp = tmp->next;
		}
		dat_tmp->lst[i] = NULL;
		dat_tmp = dat_tmp->next;
	}
}

void	ft_lstconvert(t_mnours *mini, t_exec *data)
{
	t_exec	*dat_tmp;
	t_args	*tmp;
	int		i;

	dat_tmp = data;
	i = 0;
	tmp = dat_tmp->args;
	converter(dat_tmp, tmp, mini, i);
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
char	*convert_env(t_mnours *mnours)
{
	char **env_array;
	char **temp;
	t_env *env_lst;
	int i;

	i = 0;
	env_lst = mnours->env;
	temp = ft_calloc(sizeof(char *), 2);
	env_array = ft_calloc(sizeof(char *), ft_envsize(mnours->env) + 1);
	while (env_lst)
	{
		temp[0] = ft_strjoin(env_lst->name, "=");
		env_array[i] = ft_strjoin(temp[0], env_lst->value);
		free_array(temp);
		env_lst = env_lst->next;
		i++;
	}
}
