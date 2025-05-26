/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:48:01 by abosc             #+#    #+#             */
/*   Updated: 2025/05/27 00:43:15 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	verif(t_mnours *mnours)
{
	if (check_quotes(1, mnours->line) == 1)
	{
		ft_error("Syntax Error: incorrect quotes (single)", mnours);
		mnours->exit = 1;
	}
	if (check_quotes(2, mnours->line) == 1)
	{
		ft_error("Syntax Error: incorrect quotes (double)", mnours);
		mnours->exit = 1;
	}
	return (NULL);
}

int	check_quotes(int type, char *line)
{
	int		counter;
	int		i;
	char	c;

	i = 0;
	counter = 0;
	if (type == 1)
		c = '"';
	if (type == 2)
		c = '\'';
	while (line[i])
	{
		if (line[i] == c)
			counter++;
	}
	if (counter % 2 == 1)
		return (1);
	return (0);
}
