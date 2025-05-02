/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:14:03 by alegrix           #+#    #+#             */
/*   Updated: 2025/05/02 16:19:39 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_env	*ft_envnew(char *line)
{
	t_env	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->value = line;
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
