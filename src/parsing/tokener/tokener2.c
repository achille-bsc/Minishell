/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:58:58 by abosc             #+#    #+#             */
/*   Updated: 2025/06/20 18:28:33 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	analyze_quote_type(char *str)
{
	int	len;
	int	i;
	int	in_squote;
	int	in_dquote;
	int	has_quotes;
	int	j;
	int	internal_quotes;

	j = 1;
	internal_quotes = 0;
	if (!str || !*str)
		return (NO_Q);
	len = ft_strlen(str);
	i = 0;
	in_squote = 0;
	in_dquote = 0;
	has_quotes = 0;
	while (i < len)
	{
		if (str[i] == '\'' && !in_dquote)
		{
			in_squote = !in_squote;
			has_quotes = 1;
		}
		else if (str[i] == '\"' && !in_squote)
		{
			in_dquote = !in_dquote;
			has_quotes = 1;
		}
		i++;
	}
	if (has_quotes)
	{
		if (len >= 2 && str[0] == '\"' && str[len - 1] == '\"')
		{
			while (j < len - 1)
			{
				if (str[j] == '\"')
					internal_quotes = 1;
				j++;
			}
			if (!internal_quotes)
				return (D_Q);
		}
		if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		{
			j = 1;
			while (j < len - 1)
			{
				if (str[j] == '\'')
					return (NO_Q);
				j++;
			}
			return (S_Q);
		}
		return (NO_Q);
	}
	return (NO_Q);
}
