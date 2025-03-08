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

#include "ft_printf.h"

int	ft_puthexai(unsigned long nb, char c)
{
	int		count;
	char	*hexa;

	count = 1;
	if (c == 'X')
		hexa = "0123456789ABCDEF";
	else
		hexa = "0123456789abcdef";
	if (nb >= 16)
		count += ft_puthexai(nb / 16, c);
	write(1, &hexa[nb % 16], 1);
	return (count);
}

int	ft_putnbri(int nb)
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
		write(1, "-", 1);
		sign++;
	}
	temp = (n % 10) + '0';
	n /= 10;
	if (n > 0)
		count += ft_putnbri(n);
	write(1, &temp, 1);
	return (count + sign);
}

int	ft_putnbrui(unsigned int n)
{
	char	temp;
	int		count;

	count = 1;
	temp = (n % 10) + '0';
	if (n / 10 > 0)
		count += ft_putnbrui(n / 10);
	write(1, &temp, 1);
	return (count);
}

int	ft_putptri(uintptr_t ptr)
{
	int				count;

	if (!ptr)
		return (ft_putstri("(nil)"));
	count = 0;
	if (ptr == 0)
		return (ft_putstri("(nil)"));
	else
	{
		count += write(1, "0x", 2);
		count += ft_puthexai(ptr, 'x');
	}
	return (count);
}
/*
int	main(void)
{
	printf("\n%d\n", ft_putnbrui(65467768));
}*/
