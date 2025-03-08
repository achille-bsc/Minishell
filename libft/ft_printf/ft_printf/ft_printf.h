/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:23:12 by alegrix           #+#    #+#             */
/*   Updated: 2024/11/05 08:31:41 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_puthexai(unsigned long nb, char c);
int	ft_putnbri(int nb);
int	ft_putnbrui(unsigned int n);
int	ft_putptri(uintptr_t ptr);
int	ft_putchari(char c);
int	ft_putstri(char *s);

#endif
