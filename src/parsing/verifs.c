/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:48:01 by abosc             #+#    #+#             */
/*   Updated: 2025/06/24 00:38:22 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	check_quotes2(char *c, char *c2, int type)
{
	if (type == 1)
	{
		*c = '\'';
		*c2 = '\"';
	}
	if (type == 2)
	{
		*c = '\"';
		*c2 = '\'';
	}
}

int	check_quotes(int type, char *line)
{
	int		counter;
	int		i;
	int		in_other_quote;
	char	c[2];

	i = 0;
	in_other_quote = 0;
	counter = 0;
	check_quotes2(&(c[0]), &(c[1]), type);
	while (line[i])
	{
		if (line[i] == c[1] && !in_other_quote && got_ended(line, i, c[1]))
			in_other_quote = 1;
		else if (line[i] == c[1] && in_other_quote)
			in_other_quote = 0;
		else if (line[i] == c[0] && !in_other_quote)
			counter++;
		i++;
	}
	return (check_quotes_2(c, counter));
}

void	check_chars2(char *l, int *i, int *s_quote, int *d_quote)
{
	if (l[(*i)++] == '\'' && !*d_quote)
		*s_quote = !*s_quote;
	else if (l[*i - 1] == '\"' && !*s_quote)
		*d_quote = !*d_quote;
}

int	check_chars(char *li)
{
	int	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (li[i[0]])
	{
		if (li[i[0]] == '<' && li[i[0] + 1] == '<' && li[i[0] + 2] == '<')
			return (perror("Syntax Error: near unexpected token `<<<'"), 1);
		if (li[i[0]] == '|' && li[i[0] + 1] && li[i[0] + 1] == '|')
			return (perror("Syntax Error: invalid pipe"), 1);
		if (li[i[0]] == '<' && li[i[0] + 1] && li[i[0] + 1] == '<')
		{
			while (li[i[0]] && (li[i[0]] == '\t' || li[i[0]] == ' '
					|| li[i[0]] == '<'))
				i[0]++;
			if (!li[i[0]] || li[i[0]] == '\n')
				return (perror("Parse Error: syntax error near"
						"unexpected token `newline'"),
					1);
			i[0]--;
		}
		check_chars2(li, &(i[0]), &(i[1]), &(i[2]));
	}
	return (0);
}

int	verif(t_mnours *mnours)
{
	int	i;

	if (!mnours->line || !mnours->line[0])
		return (1);
	i = 0;
	if (check_chars(mnours->line) == 1)
	{
		mnours->exit_code = 2;
		return (1);
	}
	while (mnours->line[i] && (mnours->line[i] == ' '
			|| mnours->line[i] == '\t'))
		i++;
	if (!mnours->line[i])
		return (1);
	if (check_quotes(1, mnours->line))
		return (ft_error("Syntax Error: incorrect quotes (single)", mnours), 1);
	if (check_quotes(2, mnours->line))
		return (ft_error("Syntax Error: incorrect quotes (double)", mnours), 1);
	return (0);
}
