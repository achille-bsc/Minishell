/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:47:05 by abosc             #+#    #+#             */
/*   Updated: 2025/05/20 00:53:05 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

int	handle_redir(char *prompt, int i, t_lst *word)
{
	int	j;

	j = 0;
	if (prompt[i] == prompt[i + 1])
		word->content[j++] = prompt[i++];
	word->content[j++] = prompt[i++];
	while (prompt[i] == ' ')
		i++;
	while (prompt[i] && prompt[i] != ' ' && prompt[i] != '<' && prompt[i] != '>')
		word->content[j++] = prompt[i++];
	word->next = ft_calloc(sizeof(t_lst), 1);
	if (!word->next)
		exit(1);
	return (i);
}
