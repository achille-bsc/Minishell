/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:23:12 by alegrix           #+#    #+#             */
/*   Updated: 2025/03/09 00:10:27 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int	ft_dprintf(int fd, const char *format, ...);
int	dputhexai(int fd, unsigned long nb, char c);
int	dputnbri(int fd, int nb);
int	dputnbrui(int fd, unsigned int n);
int	dputptri(int fd, uintptr_t ptr);
int	dputchari(int fd, char c);
int	dputstri(int fd, char *s);

#endif
