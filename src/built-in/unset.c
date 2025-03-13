/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:56:10 by alegrix           #+#    #+#             */
/*   Updated: 2025/03/14 00:31:06 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_unset(t_env *env, char *line)
{
	t_env	*tmp;
	t_env	*tmp_pre;

	tmp = env;
	if (ft_strcmp(tmp->line, line) == 0)
	{
		env = env->next;
		free(tmp);
	}
	while ()
	{
		tmp = tmp->next;
	}
	tmp = ft_envnew(line);
}
