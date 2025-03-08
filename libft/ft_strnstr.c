/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:04:34 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/25 01:52:28 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <bsd/string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (*little == '\0')
		return ((char *)big);
	while (*big && len)
	{
		if (*big == little[0])
		{
			i = 1;
			while (little[i] == big[i] && big[i] && i < len)
				i++;
			if (little[i] == 0)
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL);
}
/*
int	main(void)
{
	printf("%s\n", strnstr("Hello Worldelae", "World", 11));
	printf("%s\n", ft_strnstr("Hello Worldelae", "World", 11));
}
*/
