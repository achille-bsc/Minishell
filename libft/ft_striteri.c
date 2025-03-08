/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:43:17 by alegrix           #+#    #+#             */
/*   Updated: 2024/10/30 23:48:00 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
static void	testing(unsigned int i, char *s)
{
	s[i] = 'b';
}

int	main(void)
{
	char	*test;

	test = ft_strdup("Je suis un sushi.");
	ft_striteri(test, (void *)testing);
	printf("%s\n", test);
}*/
