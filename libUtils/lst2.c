/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:06:55 by abosc             #+#    #+#             */
/*   Updated: 2025/06/20 20:12:09 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**ft_tabdup(char **tab)
{
	char	**res;
	int		i;

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
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**convert_env(t_mnours *mnours)
{
	char	**env_tab;
	t_env	*tmp;
	int		i;
	int		j;
	int		k;

	if (mnours->lst_env)
		free_array(mnours->lst_env);
	i = 0;
	tmp = mnours->env;
	env_tab = ft_calloc(sizeof(char *), ft_envsize(mnours->env) + 1);
	while (tmp)
	{
		env_tab[i] = ft_calloc(1, ft_strlen(tmp->name) + ft_strlen(tmp->value)
				+ 2);
		j = ft_strlcpy(env_tab[i], tmp->name, ft_strlen(tmp->name) + 1);
		env_tab[i][j++] = '=';
		k = 0;
		while (tmp->value[k])
			env_tab[i][j++] = tmp->value[k++];
		env_tab[i][j] = '\0';
		tmp = tmp->next;
		i++;
	}
	return (env_tab[i] = NULL, env_tab);
}
