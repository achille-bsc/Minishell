/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchari.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 04:37:45 by alegrix           #+#    #+#             */
/*   Updated: 2024/11/05 08:27:38 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchari(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstri(char *s)
{
	int	i;
	int	count;

	if (!s)
		return (write(1, "(null)", 6));
	i = 0;
	count = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
		count++;
	}
	return (count);
}
