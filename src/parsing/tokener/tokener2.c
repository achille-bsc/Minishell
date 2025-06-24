/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:58:58 by abosc             #+#    #+#             */
/*   Updated: 2025/06/24 03:56:21 by alegrix          ###   ########.fr       */
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

int	hd_good(char *prompt, int i)
{
	ft_dprintf(2, "%c et %i\n", prompt[i], i);
	if ((prompt[i] != '<' && prompt[i + 1] != '<')
		|| (i != 0 && prompt[i] != '<' && prompt[i - 1] != '<'))
		return (0);
	return (1);
}

/*t_lst	*get_words(char *prompt)
{
	t_lst		*words[2];
	int			i;
	t_quotes	q;

	i = 0;
	q.sin = 0;
	q.dou = 0;
	words[1] = create_word();
	words[0] = words[1];
	while (prompt[i])
	{
		if (!q.sin && !q.dou && (prompt[i] == '<' || prompt[i] == '>'))
			i = handle_redir(prompt, i, &(words[1]));
		else if (!q.sin && !q.dou && prompt[i] == '|')
			i = capipe(prompt, i, &(words[1]));
		else if (!q.sin && !q.dou && (prompt[i] == ' ' || prompt[i] == '\t'))
			while (prompt[i] == ' ' || prompt[i] == '\t')
				i++;
		else
			i = complete(i, prompt, &(words[1]), &q);
	}
	words[1] = words[0];
	get_words2(words[1]);
	return (words[0]);
}*/
