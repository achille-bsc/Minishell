/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:39:14 by alegrix           #+#    #+#             */
/*   Updated: 2025/05/27 01:00:38 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_echo(char **line)
{
	int	nl;
	int	i;
	int	j;
	int	k;

	ft_printf("%s\n\n");
	nl = 0;
	k = 1;
	while (ft_strncmp(line[k], "-n", 2))
	{
		j = 1;
		while (line[k][j] == 'n')
			j++;
		if (!line[k][j])
			nl += 1;
		k++;
	}
	i = 1 + nl;
	while (line[i])
	{
		if (i > nl + 1)
			ft_printf(" ");
		ft_printf("%s", line[i++]);
	}
	if (nl == 0)
		ft_printf("\n");
}
