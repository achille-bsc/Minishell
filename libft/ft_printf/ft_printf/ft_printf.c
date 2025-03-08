/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:36:40 by alegrix           #+#    #+#             */
/*   Updated: 2024/11/05 08:31:21 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	ft_formatf(char symb, va_list list)
{
	int	count;

	count = 0;
	if (symb == 'c')
		count = ft_putchari(va_arg(list, int));
	else if (symb == 's')
		count = ft_putstri(va_arg(list, char *));
	else if (symb == 'p')
		count = ft_putptri(va_arg(list, uintptr_t));
	else if (symb == 'd' || symb == 'i')
		count = ft_putnbri(va_arg(list, int));
	else if (symb == 'u')
		count = ft_putnbrui(va_arg(list, unsigned int));
	else if (symb == 'x' || symb == 'X')
		count = ft_puthexai(va_arg(list, unsigned int), symb);
	else if (symb == '%')
		count = write (1, "%", 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	int		i;
	va_list	list;

	count = 0;
	i = 0;
	va_start(list, format);
	while (format[i])
	{
		if (format[i] == '%')
			count += ft_formatf(format[++i], list);
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(list);
	return (count);
}
/*
int	main(void)
{
	ft_printf("-----------------FT-----------------\n");
	ft_printf(" NULL %s NULL ", NULL);
	//ft_printf("un nombre : %d suivi d'un hexa : %x\n", 65467768, 1005);
	printf("-----------------PAFT---------------\n");
	printf(" NULL %s NULL ", NULL);
	//printf("un nombre : %d suivi d'un hexa : %x\n", 65467768, 1005);
}*/
