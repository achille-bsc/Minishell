/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:46:22 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/22 00:08:26 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nbi, int fd)
{
	long	n;
	char	temp;

	n = nbi;
	temp = 0;
	if (n < 0)
	{
		n = -n;
		write (fd, "-", 1);
	}
	temp = (n % 10) + '0';
	n = n / 10;
	if (n > 0)
		ft_putnbr_fd(n, fd);
	write (fd, &temp, 1);
}
