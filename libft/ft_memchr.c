/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:00:55 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/25 01:59:45 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*temp;

	temp = (char *)s;
	while (n--)
	{
		if (*temp == (char)c)
			return (temp);
		temp++;
	}
	return (NULL);
}

/*
int	main(void)
{
	const char	st[] = "dfs10fds0";
	int	c = '1';

	printf("%s", (char *)ft_memchr(st, c, 8));
}
*/
