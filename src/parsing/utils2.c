/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:43:02 by abosc             #+#    #+#             */
/*   Updated: 2025/06/23 21:17:52 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	got_ended(char *line, int i, char c)
{
	i += 1;
	while (line[i])
	{
		if (line[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_quotes_2(char c[2], int counter)
{
	if (counter % 2 == 1)
	{
		if (c[0] == '\"')
			return (2);
		else if (c[0] == '\'')
			return (1);
	}
	return (0);
}
