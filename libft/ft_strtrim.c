/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:47:18 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/25 01:58:14 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	len = ft_strlen(s1) - 1;
	if (!set || !s1)
		return ((char *)s1);
	i = 0;
	while (s1[i] && ft_strchr((char *)set, s1[i]))
		i++;
	while (s1[i] && ft_strchr((char *)set, s1[len]))
		len--;
	len++;
	result = malloc(len - i + 1);
	if (!result)
		return (NULL);
	j = 0;
	while (i < len)
		result[j++] = s1[i++];
	result[j] = '\0';
	return (result);
}
/*
int	main(void)
{
	printf("%s", ft_strtrim("\n  \t\t iuiiuiui\n\n \t  \n", "\n \t"));
}*/
