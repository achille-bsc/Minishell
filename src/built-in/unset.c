/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:56:10 by alegrix           #+#    #+#             */
/*   Updated: 2025/04/23 21:34:53 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_unset(t_env *env, char *line)
{
	t_env	*tmp;
	t_env	*tmp_pre;

	tmp = env;
	if (ft_strncmp(tmp->name, line, ft_strlen(line)) == 0
		&& ft_strlen(tmp->name) - 1 == ft_strlen(line))
	{
		env = env->next;
		free(tmp);
	}
	while (tmp)
	{
		tmp_pre = tmp;
		tmp = tmp->next;
		if (ft_strncmp(tmp->name, line, ft_strlen(line)) == 0
			&& ft_strlen(tmp->name) - 1 == ft_strlen(line))
		{
			tmp_pre->next = tmp->next;
			free(tmp);
			return ;
		}
	}
}
