/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:46:53 by alegrix           #+#    #+#             */
/*   Updated: 2025/03/16 01:30:12 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_export(t_env *env, char *line)
{
	t_env	*tmp;
	t_env	*pre;
	t_env	*nex;

	int		i;

	tmp = env;
	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '=')
		i++;
	while (tmp)
	{
		if (ft_strncmp(line, tmp->line, i) == 0)
		tmp = tmp->next;
	}
	tmp = ft_envnew(line);
}
