/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:09:24 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/19 21:42:54 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_exit(t_mnours *data, char **line)
{
	int	i;
	int	good;

	good = -1;
	if (data->nb_pipe < 1)
		ft_dprintf(2, "exit\n");
	data->is_exit = 1;
	if (!line[1])
		return (data->exit = data->exit_status, 0);
	i = 0;
	while (line[1][i])
	{
		if (!ft_isdigit(line[1][i]) && (i != 1 && line[1][i] != '-'))
		{
			ft_dprintf(2, "Mininours: exit: %s: numeric argument required\n",
				line[1]);
			data->exit = 2;
			return (2);
		}
		i++;
	}
	data->exit = ft_atoi(line[1]);
	return (data->exit);
}
