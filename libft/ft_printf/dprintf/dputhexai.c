/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexai.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:11:03 by alegrix           #+#    #+#             */
/*   Updated: 2024/11/05 08:27:55 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	dputhexai(int fd, unsigned long nb, char c)
{
	int		count;
	char	*hexa;

	count = 1;
	if (c == 'X')
		hexa = "0123456789ABCDEF";
	else
		hexa = "0123456789abcdef";
	if (nb >= 16)
		count += dputhexai(fd, nb / 16, c);
	write(fd, &hexa[nb % 16], 1);
	return (count);
}

int	dputnbri(int fd, int nb)
{
	long	n;
	char	temp;
	int		count;
	int		sign;

	n = nb;
	sign = 0;
	count = 1;
	if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
		sign++;
	}
	temp = (n % 10) + '0';
	n /= 10;
	if (n > 0)
		count += dputnbri(fd, n);
	write(fd, &temp, 1);
	return (count + sign);
}

int	dputnbrui(int fd, unsigned int n)
{
	char	temp;
	int		count;

	count = 1;
	temp = (n % 10) + '0';
	if (n / 10 > 0)
		count += dputnbrui(fd, n / 10);
	write(fd, &temp, 1);
	return (count);
}

int	dputptri(int fd, uintptr_t ptr)
{
	int				count;

	if (!ptr)
		return (dputstri(fd, "(nil)"));
	count = 0;
	if (ptr == 0)
		return (dputstri(fd, "(nil)"));
	else
	{
		count += write(fd, "0x", 2);
		count += dputhexai(fd, ptr, 'x');
	}
	return (count);
}
/*
int	main(void)
{
	printf("\n%d\n", ft_putnbrui(65467768));
}*/
