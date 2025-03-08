/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:24:34 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/28 20:34:16 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *s, char c)
{
	int	in_words;
	int	count;

	count = 0;
	in_words = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c && in_words == 0)
		{
			in_words = 1;
			count++;
		}
		else if (*s == c)
		{
			in_words = 0;
		}
		s++;
	}
	return (count);
}

char	*splitting(char *splitter, char *s, int *i, char c)
{
	int	start;
	int	len;

	len = 0;
	while (s[*i] && s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] && s[*i] != c)
	{
		len++;
		(*i)++;
	}
	splitter = ft_substr((char *)s, start, len);
	return (splitter);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc((count_words((char *)s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (j < count_words ((char *)s, c))
	{
		result[j] = splitting(result[j], (char *)s, &i, c);
		if (!result[j])
		{
			while (j--)
				free(result[j]);
			free(result);
			return (NULL);
		}
		j++;
	}
	result[j] = NULL;
	return (result);
}
/*
int	main(void)
{
	char	**result;
	int	i = 0;

	result = ft_split("Tripouille", ' ');
	while (result[i] != NULL)
	{
		printf("%s\n", result[i]);
		i++;
	}
	i = 0;
	while(result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}*/
