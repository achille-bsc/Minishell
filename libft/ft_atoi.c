/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:07:30 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/25 02:00:30 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char *nbr)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (nbr[i] == 32 || (nbr[i] > 8 && nbr[i] < 14))
		i++;
	if (nbr[i] == '+' || nbr[i] == '-')
	{
		if (nbr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
		result = result * 10 + nbr[i++] - '0';
	result *= sign;
	return (result);
}
/*
int	main(void)
{
	printf("%d\n", ft_atoi("  -543345"));
	printf("%d\n", atoi("  +543345"));
}
*/
