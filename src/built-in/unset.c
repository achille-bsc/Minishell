/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:56:10 by alegrix           #+#    #+#             */
/*   Updated: 2025/05/27 00:49:33 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_env	*ft_unset2(t_env *env, char *line)
{
	t_env	*init_env;
	t_env	*tmp;

	init_env = env;
	if (ft_strncmp(env->name, line, ft_strlen(line)) == 0
		&& ft_strlen(env->name) - 1 == ft_strlen(line))
	{
		init_env = init_env->next;
		free(env);
		return (init_env);
	}
	while (env)
	{
		tmp = env;
		env = env->next;
		if (ft_strncmp(env->name, line, ft_strlen(line)) == 0
			&& ft_strlen(env->name) - 1 == ft_strlen(line))
		{
			tmp->next = env->next;
			free(env);
			return (init_env);
		}
	}
	return (init_env);
}

t_env	*ft_unset(t_env *env, char **line)
{
	int		i;
	t_env	*first_env;

	first_env = env;
	i = 1;
	while (line[i])
		first_env = ft_unset2(env, line[i++]);
	return (first_env);
}
