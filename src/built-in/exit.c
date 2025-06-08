/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:09:24 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/01 07:50:50 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_exit(t_mnours *data, char **line)
{
	int	i;

	ft_printf("exit\n");
	data->is_exit = 1;

	if (!line[1])
	{
		data->exit = data->exit_status;
		return ;
	}

	i = 0;
	while (line[1][i])
	{
		if (!ft_isdigit(line[1][i]))
		{
			ft_printf("Mininours: exit: %s: numeric argument required\n", line[1]);
			data->exit = 2;
			return ;
		}
		i++;
	}
	data->exit = ft_atoi(line[1]);
}
