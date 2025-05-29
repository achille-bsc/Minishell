/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 02:03:23 by abosc             #+#    #+#             */
/*   Updated: 2025/05/29 02:28:46 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_env	*set_env(char **env)
{
	t_env	*head;
	t_env	*current;
	int		i;

	head = ft_calloc(sizeof(t_env), 1);
	if (!head)
		return (NULL);
	current = head;
	i = 0;
	while (env[i])
	{
		env_create_node(&current, env[i]);
	}
}

void	env_create_node(t_env *current, char *env_var)
{
	char	**split_values;

	split_values = ft_split(env_var, '=');
	if (!split_values || !split_values[0])
	{
		free(current);
		return (NULL);
	}
	if (!split_values[0] || !split_values[1])
	{
		free(split_values);
		return ;
	}
	current->name = ft_strdup(split_values[0]);
	current->value = ft_strdup(split_values[1]);
	current->next = ft_calloc(sizeof(t_env), 1);
	if (!current->next)
	{
		free(current->name);
		free(current->value);
		free(current);
		return (NULL);
	}
	current = current->next;
	free(split_values[0]);
}
