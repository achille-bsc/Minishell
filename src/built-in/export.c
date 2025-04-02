/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:46:53 by alegrix           #+#    #+#             */
/*   Updated: 2025/04/02 22:11:09 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_export(t_env *env, char **line)
{
	t_env	*tmp;
	t_env	*pre;
	t_env	*next;
	int		i;

	if (line[1] == NULL)
		ft_env(env);
	tmp = env;
	pre = NULL;
	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '=')
		i++;
	while (tmp)
	{
		if (ft_strncmp(line, tmp->line, i) == 0)
		{
			free(tmp->line);
			tmp->line = line;
			return ;
		}
		tmp = tmp->next;
	}
	tmp = ft_envnew(line);
}
