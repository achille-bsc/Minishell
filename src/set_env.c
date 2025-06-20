/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:14:03 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/20 17:44:37 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_env	*ft_envnew(char *line)
{
	t_env	*new;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	name = find_name(line, &i);
	value = find_value(line, &i);
	if (name)
		new->name = ft_strdup(name);
	else
		new->name = ft_strdup("\0");
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = ft_strdup("\0");
	free(name);
	free(value);
	new->next = NULL;
	return (new);
}

void	update_env(t_mnours *mnours, char *var_name, char *new_value)
{
	t_env	*env;

	env = mnours->env;
	while (env)
	{
		if (ft_strncmp(env->name, var_name, ft_strlen(var_name)) == 0
			&& ft_strlen(env->name) == ft_strlen(var_name))
		{
			free(env->value);
			env->value = ft_strdup(new_value);
			return ;
		}
		env = env->next;
	}
	mnours->lst_env = convert_env(mnours);
}

void	set_env(t_mnours *g, char **env)
{
	int		i;
	t_env	*current;
	t_env	*new_env;

	if (!env || !env[0])
		return ;
	g->env = ft_envnew(env[0]);
	current = g->env;
	i = 1;
	while (env[i])
	{
		new_env = ft_envnew(env[i]);
		if (new_env)
		{
			current->next = new_env;
			current = new_env;
		}
		i++;
	}
}

t_env	*get_env(t_mnours *mnours, char *var)
{
	t_env	*env;

	env = mnours->env;
	while (env)
	{
		if (!ft_strncmp(env->name, var, ft_strlen(var))
			&& ft_strlen(env->name) == ft_strlen(var))
			return (env);
		env = env->next;
	}
	return (NULL);
}
