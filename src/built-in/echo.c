/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:39:14 by alegrix           #+#    #+#             */
/*   Updated: 2025/04/30 23:30:47 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_echo(char **line)
{
	int	nl;
	int	i;

	nl = 0;
	if (ft_strncmp(line[1], "-n", 2) == 0)
		nl = 1;
	i = nl + 1;
	while (line[i])
	{
		if (i > 1 || (i == 1 && nl == 0))
			ft_printf(" ");
		ft_printf("%s", line[i++]);
	}
	if (nl == 0)
		ft_printf("\n");
}
