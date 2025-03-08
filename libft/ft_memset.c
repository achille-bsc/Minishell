/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:02:14 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/19 17:33:12 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t count)

{
	size_t			i;
	unsigned char	*editable;

	i = 0;
	editable = ptr;
	while (i < count)
		editable[i++] = value;
	return (ptr);
}
