/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:43:02 by abosc             #+#    #+#             */
/*   Updated: 2025/06/24 05:41:23 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check3(char *l, int i, int j, int k)
{
	if (l[i == '<' && l[i + 1] == '<' && l[i] + 2] == '<' && !(j || k))
		return (perror("Syntax Error: near unexpected token `<<<'"), 1);
	if (l[i] == '|' && l[i + 1] && l[i + 1] == '|' && !(j || k))
		return (perror("Syntax Error: invalid pipe"), 1);
	return (0);
}

void	check_quote_redir(int *j, char *lne)
{
	int	inquote[2];

	inquote[0] = 0;
	inquote[1] = 0;
	while (lne[*j] && lne[*j] != ' ' && lne[*j] != '<' && lne[*j] != '>'
		&& lne[*j] != '|')
	{
		if (lne[*j] == '\'' || lne[*j] == '\"')
		{
			if (inquote[0] && inquote[0] == 0 && lne[*j] == '\'')
				inquote[0] = 1;
			else if (inquote[0] == 1 && lne[*j] == '\'')
				inquote[0] = 0;
			else if (inquote[1] == 0 && lne[*j] == '\"')
				inquote[1] = 1;
			else if (inquote[1] == 1 && lne[*j] == '\"')
				inquote[1] = 0;
		}
		(*j)++;
	}
}

int	redirquote(char *line, int i, t_quotes *q)
{
	if (line[i] == '\"' && !q->sin)
		q->dou = !q->dou;
	else if (line[i] == '\'' && !q->dou)
		q->sin = !q->sin;
	if (q->sin || q->dou)
		return (1);
	return (0);
}

int	handle2(int *dbl, int j, char *lne, int i)
{
	if (lne[j] == lne[j - 1])
		j++;
	*dbl = j - i + 1;
	while (lne[j] == ' ')
		j++;
	return (j);
}

int	handle_redir(char *lne, int i, t_lst **word)
{
	int			j;
	int			tmp;
	int			dbl;
	t_quotes	q;

	q.sin = 0;
	q.dou = 0;
	j = i + 1;
	dbl = 0;
	tmp = handle2(&dbl, j, lne, i);
	check_quote_redir(&j, lne);
	(*word)->content = ft_calloc(sizeof(char), ft_strlen(lne) + 1);
	j = 0;
	if (lne[i] == lne[i + 1])
		(*word)->content[j++] = lne[i++];
	(*word)->content[j++] = lne[i++];
	i = tmp;
	while (lne[i] && (redirquote(lne, i, &q) == 1 || (lne[i] != ' '
				&& lne[i] != '<' && lne[i] != '>' && lne[i] != '|')))
		(*word)->content[j++] = lne[i++];
	(*word)->next = ft_calloc(sizeof(t_lst), 1);
	return ((*word) = (*word)->next, i);
}
