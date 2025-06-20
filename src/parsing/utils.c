/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:47:05 by abosc             #+#    #+#             */
/*   Updated: 2025/06/20 19:47:36 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <readline/readline.h>

t_lst	*create_word(void)
{
	t_lst	*word;

	word = ft_calloc(sizeof(t_lst), 1);
	if (!word)
		return (NULL);
	return (word);
}

void	check_args(t_exec *exec)
{
	t_exec	*tmp;
	t_args	*pre_tmpa;
	t_args	*tmpa;

	tmp = exec;
	while (tmp)
	{
		tmpa = tmp->args;
		while (tmpa)
		{
			if (!tmpa->name)
			{
				pre_tmpa->next = NULL;
				free_args(tmpa);
			}
			else if (tmpa->name[0] == ' ' || tmpa->name[0] == '\0')
			{
				pre_tmpa->next = NULL;
				free_args(tmpa);
			}
			pre_tmpa = tmpa;
			tmpa = tmpa->next;
		}
		tmp = tmp->next;
	}
}

int	complete(int i, char *line, t_lst **word, t_quotes *q)
{
	int			j;
	t_quotes	tmp;
	int			k;

	j = i;
	tmp.sin = (*q).sin;
	tmp.dou = (*q).dou;
	while (line[j])
	{
		set_quotes(line[j++], &tmp);
		if (!tmp.sin && !tmp.dou && (line[j] == '<'
				|| line[j] == '>' || line[j] == ' ' || line[j] == '\t'
				|| line[j] == '|'))
			break ;
	}
	(*word)->content = ft_calloc(sizeof(char), j - i + 1);
	k = 0;
	while (i < j && line[i])
	{
		(*word)->content[k++] = line[i];
		set_quotes(line[i++], q);
	}
	(*word)->next = ft_calloc(sizeof(t_lst), 1);
	return ((*word) = (*word)->next, i);
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

int	handle_redir(char *lne, int i, t_lst **word)
{
	int	j;
	int	tmp;
	int	dbl;

	j = i + 1;
	if (lne[j] == lne[j - 1])
		j++;
	dbl = j - i + 1;
	while (lne[j] == ' ')
		j++;
	tmp = j;
	check_quote_redir(&j, lne);
	(*word)->content = ft_calloc(sizeof(char), j - tmp + dbl + 1);
	j = 0;
	if (lne[i] == lne[i + 1])
		(*word)->content[j++] = lne[i++];
	(*word)->content[j++] = lne[i++];
	i = tmp;
	while (lne[i] && lne[i] != ' ' && lne[i] != '<' && lne[i] != '>'
		&& lne[i] != '|')
		(*word)->content[j++] = lne[i++];
	(*word)->next = ft_calloc(sizeof(t_lst), 1);
	return ((*word) = (*word)->next, i);
}
