/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:14:03 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/11 00:07:49 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_env	*ft_envnew(char *line)
{
	t_env	*new;
	char	**split_result;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	split_result = ft_split(line, '=');
	if (!split_result)
	{
		free(new);
		return (NULL);
	}
	if (split_result[0])
		new->name = ft_strdup(split_result[0]);
	else
		new->name = ft_strdup("\0");
	if (split_result[1])
		new->value = ft_strdup(split_result[1]);
	else
		new->value = ft_strdup("\0");
	free_array(split_result);
	new->next = NULL;
	return (new);
}

void update_env(t_mnours *mnours, char *var_name, char *new_value)
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
			return;
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
		return;
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
		if (!ft_strncmp(env->name, var, ft_strlen(var)))
			return (env);
		env = env->next;
	}
	return (NULL);
}
