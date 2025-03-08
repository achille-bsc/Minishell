/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:36:40 by alegrix           #+#    #+#             */
/*   Updated: 2025/03/08 22:52:28 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include <stdarg.h>

static int	dformatf(int fd, char symb, va_list list)
{
	int	count;

	count = 0;
	if (symb == 'c')
		count = dputchari(fd, va_arg(list, int));
	else if (symb == 's')
		count = dputstri(fd, va_arg(list, char *));
	else if (symb == 'p')
		count = dputptri(fd, va_arg(list, uintptr_t));
	else if (symb == 'd' || symb == 'i')
		count = dputnbri(fd, va_arg(list, int));
	else if (symb == 'u')
		count = dputnbrui(fd, va_arg(list, unsigned int));
	else if (symb == 'x' || symb == 'X')
		count = dputhexai(fd, va_arg(list, unsigned int), symb);
	else if (symb == '%')
		count = write (fd, "%", 1);
	return (count);
}

int	ft_dprintf(int fd, const char *format, ...)
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
			count += dformatf(fd, format[++i], list);
		else
			count += write(fd, &format[i], 1);
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
