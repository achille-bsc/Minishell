/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:56:10 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/19 15:06:20 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_env	*ft_unset2(t_env *env, char *line)
{
	t_env	*init_env;
	t_env	*tmp;

	if (!env || !line)
		return (env);
	init_env = env;
	// Vérifier si c'est le premier élément à supprimer
	if (ft_strncmp(env->name, line, ft_strlen(line)) == 0
		&& ft_strlen(env->name) == ft_strlen(line))
	{
		init_env = init_env->next;
		free(env->name);
		free(env->value);
		free(env);
		return (init_env);
	}
	// Parcourir le reste de la liste
	while (env->next)
	{
		if (ft_strncmp(env->next->name, line, ft_strlen(line)) == 0
			&& ft_strlen(env->next->name) == ft_strlen(line))
		{
			tmp = env->next;
			env->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return (init_env);
		}
		env = env->next;
	}
	return (init_env);
}

t_env	*ft_unset(t_env *env, char **line, t_mnours *mnours)
{
	int		i;
	t_env	*current_env;

	if (!env || !line)
		return (env);
	current_env = env;
	i = 1;
	while (line[i])
	{
		current_env = ft_unset2(current_env, line[i]);
		i++;
	}
	mnours->lst_env = convert_env(mnours);
	mnours->exit_code = 0;
	return (current_env);
}
