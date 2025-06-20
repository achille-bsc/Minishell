/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:05:54 by abosc             #+#    #+#             */
/*   Updated: 2025/06/20 17:18:37 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	get_array_size(char **array)
{
	int	size;

	size = 0;
	if (!array)
		return (0);
	while (array[size])
		size++;
	return (size);
}

char	*ft_getenv(char *name, t_env *env)
{
	t_env	*cpy_env;

	cpy_env = env;
	while (cpy_env)
	{
		if (ft_strncmp(cpy_env->name, name, ft_strlen(name) + 1) == 0)
			return (cpy_env->value);
		cpy_env = cpy_env->next;
	}
	return (NULL);
}
