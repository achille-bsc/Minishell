/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:47:05 by abosc             #+#    #+#             */
/*   Updated: 2025/06/24 03:39:47 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <readline/readline.h>

int	got_ended(char *line, int i, char c)
{
	i += 1;
	while (line[i])
	{
		if (line[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_quotes_2(char c[2], int counter)
{
	if (counter % 2 == 1)
	{
		if (c[0] == '\"')
			return (2);
		else if (c[0] == '\'')
			return (1);
	}
	return (0);
}

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
