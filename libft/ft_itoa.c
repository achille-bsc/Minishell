/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:42:44 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/25 01:54:25 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_count(long n)
{
	int	count;

	count = 2;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*rev_tab(char *result)
{
	char	temp;
	int		i;
	int		j;

	j = ft_strlen(result) - 1;
	i = 0;
	if (result[0] == '-')
		i = 1;
	while (i < j)
	{
		temp = result[i];
		result[i++] = result[j];
		result[j--] = temp;
	}
	result[ft_strlen(result)] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		count;
	char	*result;
	int		i;

	nb = (long)n;
	count = itoa_count(nb);
	result = ft_calloc(count, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	if (nb < 0)
	{
		nb = -nb;
		result[0] = '-';
		i = 1;
	}
	while (nb > 0)
	{
		result[i++] = (nb % 10) + '0';
		nb /= 10;
	}
	if (result[0] == '\0')
		result[0] = '0';
	return (rev_tab(result));
}
/*
int	main(void)
{
	printf("%s", ft_itoa(0));
}*/
