/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:58:58 by abosc             #+#    #+#             */
/*   Updated: 2025/06/24 05:25:14 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	set_quotes(char prompt, t_quotes *q)
{
	if (prompt == '\'' && !((*q).dou))
	{
		(*q).sin = !((*q).sin);
	}
	else if (prompt == '\"' && !((*q).sin))
	{
		(*q).dou = !((*q).dou);
	}
}

int	analyze2(char *str, int has_quotes, int len)
{
	int	nb[2];

	nb[0] = 1;
	nb[1] = 0;
	if (has_quotes)
	{
		if (len >= 2 && str[0] == '\"' && str[len - 1] == '\"')
		{
			while (nb[0] < len - 1)
				if (str[nb[0]++] == '\"')
					nb[1] = 1;
			if (!nb[1])
				return (D_Q);
		}
		if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		{
			nb[0] = 1;
			while (nb[0] < len - 1)
				if (str[nb[0]++] == '\'')
					return (NO_Q);
			return (S_Q);
		}
		return (NO_Q);
	}
	return (NO_Q);
}

int	analyze_quote_type(char *str)
{
	int			nb[2];
	t_quotes	q;
	int			has_quotes;

	if (!str || !*str)
		return (NO_Q);
	nb[1] = ft_strlen(str);
	nb[0] = 0;
	q.sin = 0;
	q.dou = 0;
	has_quotes = 0;
	while (nb[0] < nb[1])
	{
		if (str[nb[0]++] == '\'' && !q.dou)
		{
			q.sin = !q.sin;
			has_quotes = 1;
		}
		else if (str[nb[0] - 1] == '\"' && !q.sin)
		{
			q.dou = !q.dou;
			has_quotes = 1;
		}
	}
	return (analyze2(str, has_quotes, nb[1]));
}

void	get_words2(t_lst *words)
{
	while ((words)->next && (words)->next->content)
		(words) = words->next;
	if ((words)->next)
	{
		free((words)->next);
		words->next = NULL;
	}
}

