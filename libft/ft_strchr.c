/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 01:49:34 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/25 01:51:51 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			break ;
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}
/*
int	main(void)
{
	const char	st[] = "dfs\n0fds0";
	int	c = '\n';

	printf("%s", strchr(st, c));
}


char temp[] = "1d5435162";
*temp == '1'
temp++;
*temp == 'd'
temp++;
*temp == '5'
*/
