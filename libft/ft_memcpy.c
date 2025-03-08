/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:39:34 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/21 21:54:39 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*ed_src;
	char		*ed_dest;

	ed_src = src;
	ed_dest = dest;
	i = 0;
	if (dest == src || n == 0)
		return (dest);
	while (i < n)
	{
		ed_dest[i] = ed_src[i];
		i++;
	}
	return (dest);
}
