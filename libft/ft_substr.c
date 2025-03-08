/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:39:55 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/25 02:01:10 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;

	if (len + start <= ft_strlen(s))
	{
		result = malloc(len + 1);
		if (!result)
			return (NULL);
		ft_strlcpy(result, s + start, len + 1);
	}
	else if (start >= ft_strlen(s))
	{
		result = ft_calloc(1, sizeof(char));
		if (!result)
			return (NULL);
	}
	else
	{
		result = malloc(ft_strlen(s) - start + 1);
		if (!result)
			return (NULL);
		ft_strlcpy(result, s + start, ft_strlen(s) - start + 1);
	}
	return (result);
}
/*
int	main(void)
{
	printf("%s", ft_substr("0123456789", 3, 3));
}*/
