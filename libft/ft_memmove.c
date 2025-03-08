/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:17:55 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/21 22:47:42 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*local_dest;
	unsigned const char	*local_src;

	local_dest = dest;
	local_src = src;
	if (!dest && !src)
		return (NULL);
	if (local_dest > local_src)
		while (n--)
			local_dest[n] = local_src[n];
	else
	{
		i = 0;
		while (i < n)
		{
			local_dest[i] = local_src[i];
			i++;
		}
	}
	return (dest);
}
