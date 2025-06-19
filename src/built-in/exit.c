/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:09:24 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/19 22:11:22 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_exit(t_mnours *data, char **line)
{
	int	i;

	// int	cocher;
	// cocher = 0;
	if (data->nb_pipe < 1)
		ft_dprintf(2, "exit\n");
	// if (data->nb_pipe < 1)
	// 	data->is_exit = 1;
	if (!line[1])
		return (data->exit = data->exit_status, 0);
	i = 0;
	while (line[1][i])
	{
		if (!ft_isdigit(line[1][i]) && (i > 0 && line[1][i] == '-'))
		{
				ft_printf("%i\n", i);
				data->is_exit = 1;
				ft_dprintf(2, "Mininours: exit: %s: numeric argument required\n", line[1]);
				data->exit = 2;
				return (2);
		}
		i++;
	}
	if (get_array_size(line) > 2)
	{
		ft_dprintf(2, "Mininours: exit: too many arguments\n");
		// data->exit = 0;
		return (1);
	}
	data->is_exit = 1;
	data->exit = ft_atoi(line[1]);
	return (data->exit);
}
