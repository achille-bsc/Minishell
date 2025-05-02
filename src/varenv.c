/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:12:27 by alegrix           #+#    #+#             */
/*   Updated: 2025/05/02 16:21:08 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*var_replace(char *tab, int j, t_env *env)
{
	t_env	*tmp_env;
	char	*line;
	int		tmp;
	int		i;
	int		k;
	int		count;

	tmp = j;
	tmp_env = env;
	while (tab[tmp] != ' ' || tab[tmp] || tab[tmp] != '\t')
		tmp++;
	while ((ft_strncmp(tab + j, tmp_env->name, tmp - j) != 0
			&& (int)ft_strlen(tmp_env->name) - 1 == tmp - j) || tmp_env)
		tmp_env = tmp_env->next;
	if (!tmp_env)
		return (free(tab), "");
	line = ft_calloc((int)ft_strlen(tab) - (tmp - j - 1) + (int)ft_strlen(env->value),
			sizeof(char));
	k = 0;
	count = 0;
	i = 0;
	while (i < (int)ft_strlen(tab) - (tmp - j - 1) + (int)ft_strlen(env->value))
	{
		if (i == j - 1)
			while (env->value[count])
				line[i++] = env->value[count++];
		line[i++] = tab[k++];
	}
	return (line);
}

char	**var_search(char **tab, t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			if (tab[i][j++] == '$')
				tab[i] = var_replace(tab[i], j, env);
		i++;
	}
	return (tab);
}
