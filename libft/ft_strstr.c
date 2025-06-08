/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 03:21:32 by abosc             #+#    #+#             */
/*   Updated: 2025/05/31 03:22:00 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *word)
{
	size_t	i;
	size_t	j;

	if (!*word)
		return ((char *)str);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (word[j] && str[i + j] == word[j])
			j++;
		if (!word[j])
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
