/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:30:01 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/23 00:58:28 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

/*
int	main(void)
{
	const char	st[] = "adfs\n0ifds0fddsfia";

	printf("%s", ft_strrchr(st, 'a'));
}
*/
/*
char temp[] = "1d5435162";
*temp == '1'
temp++;
*temp == 'd'
temp++;
*temp == '5'
*/
