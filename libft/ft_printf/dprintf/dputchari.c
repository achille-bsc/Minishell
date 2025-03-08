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

int	dputchari(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	dputstri(int fd, char *s)
{
	int	i;
	int	count;

	if (!s)
		return (write(fd, "(null)", 6));
	i = 0;
	count = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
		count++;
	}
	return (count);
}
