/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:46:49 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/19 20:30:18 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	s1[100] = "5f3d4gf21vc5f";
	char	s2[100] = "5f3d4gf21vc5f";
	char	s3[100] = "519";
	char	s4[100] = "521";

	assert(ft_strncmp(s1, s2, 50) == 0);
	assert(ft_strncmp(s3, s4, 50) < 0);
	assert(ft_strncmp(s4, s3, 50) > 0);
	assert(ft_strncmp(s4, s3, 1) == 0);
	assert(ft_strncmp(s4, s3, 0) == 0);
	assert(ft_strncmp(s4, s3, 2) > 0);
	assert(ft_strncmp("", "", 0) == 0);
	assert(ft_strncmp(" ", "", 50) > 0);
	assert(ft_strncmp("", " ", 1) < 0);
}
*/
