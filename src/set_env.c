/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:14:03 by alegrix           #+#    #+#             */
/*   Updated: 2025/05/31 04:55:42 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_env	*ft_envnew(char *line)
{
	t_env	*new;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	new->name = ft_split(line, '=')[0];
	new->value = ft_split(line, '=')[1];
	new->next = NULL;
	return (new);
}

void	set_env(t_mnours *g, char **env)
{
	int		i;
	t_env	*tmp;

	g->env = ft_envnew(env[0]);
	tmp = g->env;
	tmp = tmp->next;
	i = 1;
	while (env[i])
	{
		tmp = ft_envnew(env[i++]);
		tmp = tmp->next;
	}
}


// void	set_env(t_mnours *g, char **env)
// {
// 	int i;
// 	t_env *own_env;
// 	t_env *env_head;

// 	own_env = ft_envnew(env[0]);
// 	i = 1;
// 	while(env[i])
// 	{
// 		own_env->next = ft_calloc(sizeof(t_env), 1);
// 		own_env = own_env->next;
// 		own_env = ft_envnew(env[i]);
// 	}
// }

t_env	*get_env(t_mnours *mnours, char *var)
{
	t_env	*env;

	env = mnours->env;
	while (env)
	{
		if (!strncmp(env->name, var, ft_strlen(var)))
			return (env);
		env = env->next;
	}
	return (NULL);
}
