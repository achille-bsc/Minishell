/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:30:28 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/22 01:45:01 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_bzero(void *ptr, size_t count)

{
	size_t			i;
	unsigned char	*editable;

	i = 0;
	editable = ptr;
	while (i < count)
		editable[i++] = '\0';
}
