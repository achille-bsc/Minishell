/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:47:05 by abosc             #+#    #+#             */
/*   Updated: 2025/05/20 18:59:07 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <readline/readline.h>

t_lst	*create_word(void)
{
	t_lst	*word;

	word = ft_calloc(sizeof(t_lst), 1);
	if (!word)
		exit(1);
	return (word);
}

int	set_quote(char c, int in_quote)
{
	if (in_quote == 0 && c == '\'')
		in_quote = 1;
	else if (in_quote == 1 && c == '\'')
		in_quote = 0;
	if (in_quote == 0 && c == '\"')
		in_quote = 2;
	else if (in_quote == 2 && c == '\"')
		in_quote = 0;
	return (in_quote);
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
			if (tmpa->name[0] == ' ' || tmpa->name[0] == '\0')
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

int	complete(int i, char *line, t_lst **word, int *in_quote)
{
	int	j;
	int	tmp_quote;

	j = i;
	tmp_quote = *in_quote;
	while ((tmp_quote || (line[j] != '<' && line[j] != '>' && line[j] != ' '
				&& line[j] != '\t' && line[j] != '|')) && line[j])
		tmp_quote = set_dquote(line[j++], tmp_quote);
	(*word)->content = ft_calloc(sizeof(char), j - i + 1);
	if (!(*word)->content)
		exit(1);
	j = 0;
	while ((*in_quote || (line[i] != '<' && line[i] != '>' && line[i] != ' '
				&& line[i] != '\t' && line[i] != '|')) && line[i])
		(*word)->content[j++] = line[i++];
	(*word)->next = ft_calloc(sizeof(t_lst), 1);
	(*word) = (*word)->next;
	return (i);
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
	while (lne[j] && lne[j] != ' ' && lne[j] != '<' && lne[j] != '>')
		j++;
	(*word)->content = ft_calloc(sizeof(char), j - tmp + dbl + 1);
	if (!(*word)->content)
		exit(1);
	j = 0;
	ft_printf("line %s\nchar %c\nindice %d\n", lne, lne[i], i);
	if (lne[i] == lne[i + 1])
		(*word)->content[j++] = lne[i++];
	(*word)->content[j++] = lne[i++];
	i = tmp;
	while (lne[i] && lne[i] != ' ' && lne[i] != '<' && lne[i] != '>')
		(*word)->content[j++] = lne[i++];
	(*word)->next = ft_calloc(sizeof(t_lst), 1);
	return ((*word) = (*word)->next, i);
}
