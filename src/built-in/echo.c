/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:39:14 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/13 02:00:46 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// void	ft_echo(char **line)
// {
// 	int	nl;
// 	int	i;
// 	int	j;
// 	int	k;

// 	nl = 0;
// 	k = 1;
// 	if (!line[1] || (line[1][0] == '-' && line[1][1] == 'n' && !line[1][2]))
// 	{
// 		ft_printf("\n");
// 		return ;
// 	}
// 	while (!ft_strncmp(line[k], "-n", 2))
// 	{
// 		j = 1;
// 		while (line[k][j] == 'n')
// 			j++;
// 		if (!line[k][j])
// 			nl += 1;
// 		k++;
// 	}
// 	i = 1 + nl;
// 	while (line[i])
// 	{
// 		if (i > nl + 1)
// 			ft_printf(" ");
// 		ft_printf("%s", line[i++]);
// 	}
// 	if (nl == 0)
// 		ft_printf("\n");
// }

int	skip_opt(char **line)
{
	int	i;
	int	j;
	int	counter;

	i = 1;
	j = 1;
	counter = 0;
	while (line[i])
	{
		if (line[i][0] == '-')
		{
			while (line[i][j])
			{
				if (line[i][j] != 'n')
					return (counter);
				j++;
			}
		}
		else
			return (counter);
		i++;
		counter++;
	}
	return (counter);
}

int	get_opt(char **line)
{
	int	i;

	i = 1;
	if (line[1][0] == '-')
	{
		while (line[1][i])
		{
			if (line[1][i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

int	is_only_opt(char **line)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (line[i])
	{
		if (line[i][0] == '-')
		{
			while (line[i][j])
			{
				if (line[i][j] != 'n')
					return (0);
				j++;
			}
		}
		else
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **line)
{
	int	i;
	int	skip_line;

	i = 1;
	skip_line = 1;
	if (!line[1])
		return (ft_printf("\n"));
	if (is_only_opt(line))
		return (0);
	if (get_opt(line))
		skip_line = 0;
	i += skip_opt(line);
	while (line[i])
	{
		if ((int)write(1, line[i], (int)ft_strlen(line[i])) == -1)
			return (ft_dprintf(2, "No space in the outfile\n"));
		if (line[i + 1])
			ft_printf(" ");
		i++;
	}
	if (skip_line)
		ft_printf("\n");
	return (0);
}
