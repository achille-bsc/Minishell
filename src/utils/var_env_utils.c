/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:59:24 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/23 22:00:17 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	iffree(char *str, int *k)
{
	if (*k == 1)
	{
		free(str);
		*k = 0;
	}
}

void	replace_mid(t_quotes *q, char *v, int i)
{
	if (v[i] == '\'' && !q->dou)
		q->sin = !q->sin;
	else if (v[i] == '\"' && !q->sin)
		q->dou = !q->dou;
}
