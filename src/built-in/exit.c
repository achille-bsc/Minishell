/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:09:24 by alegrix           #+#    #+#             */
/*   Updated: 2025/05/23 21:46:27 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_exit(t_mnours *data, char **line)
{
	int	i;

	data->is_exit = 1;
	i = 0;
	if (!line[1])
		return ;
	while (line[1][i])
	{
		if (ft_isdigit(line[1][i++] == 0))
		{
			ft_printf("Mininours : %s isn't a numeric value\n", line[1]);
			return ;
		}
	}
	data->exit = ft_atoi(line[1]);
}
