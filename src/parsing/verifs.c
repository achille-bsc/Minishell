/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:48:01 by abosc             #+#    #+#             */
/*   Updated: 2025/06/20 17:58:27 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_quotes(int type, char *line)
{
	int		counter;
	int		i;
	int		inquote;
	char	c[2];

	i = 0;
	inquote = 0;
	counter = 0;
	if (type == 1)
	{
		c[0] = '\'';
		c[1] = '\"';
	}
	if (type == 2)
	{
		c[0] = '\"';
		c[1] = '\'';
	}
	while (line[i])
	{
		if (line[i] == c[0] && !inquote)
			counter++;
		if (line[i] == c[1])
			inquote = !inquote;
		i++;
	}
	if (counter % 2 == 1)
	{
		if (c[0] == '\"')
			return (2);
		else if (c[0] == '\'')
			return (1);
	}
	return (0);
}

int	check_chars(char *line)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] && line[i + 1] == '|')
			return (perror("Syntax Error: invalid pipe"), 1);
		if (line[i] == '>' && line[i + 1] && line[i + 1] == '|')
			return (perror("Parse Error: unexpected token `|'"), 1);
		if (line[i] == '<' && line[i + 1] && line[i + 1] == '<')
		{
			while (line[i] && (line[i] == '\t' || line[i] == ' '
					|| line[i] == '<'))
				i++;
			if (!line[i] || line[i] == '\n')
			{
				perror("Parse Error: syntax error near unexpected token `newline'");
				return (1);
			}
			i--;
		}
		if (line[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (line[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		i++;
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
	if (mnours->line[0] == '"' && mnours->line[1] == '"')
		return (ft_error("Syntax Error: empty double quotes", mnours), 1);
	if (mnours->line[0] == '\'' && mnours->line[1] == '\'')
		return (ft_error("Syntax Error: empty single quotes", mnours), 1);
	return (0);
}
