/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:24:19 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/22 20:36:22 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*sn_1;
	unsigned char	*sn_2;

	sn_1 = (unsigned char *)s1;
	sn_2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (sn_1[i] != sn_2[i])
			return (sn_1[i] - sn_2[i]);
		i++;
	}
	return (0);
}
