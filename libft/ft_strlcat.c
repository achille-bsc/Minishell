/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:18:44 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/23 00:46:40 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(dst);
	i = 0;
	if (len >= size)
		return (ft_strlen(src) + size);
	while (src[i] && i + len < size - 1)
	{
		dst[i + len] = src[i];
		i++;
	}
	dst[i + len] = 0;
	return (len + ft_strlen(src));
}
