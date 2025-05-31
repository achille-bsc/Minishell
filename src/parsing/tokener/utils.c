/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:51:26 by abosc             #+#    #+#             */
/*   Updated: 2025/05/26 23:54:00 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	set_dquote(char prompt, int in_quote)
{
	if (prompt == '"')
		in_quote = !in_quote;
	return (in_quote);
}

int	capipe(char *prompt, int i, t_lst **word)
{
	(*word)->content = ft_calloc(sizeof(char), 2);
	(*word)->content[0] = prompt[i++];
	(*word)->next = ft_calloc(sizeof(t_lst), 1);
	(*word) = (*word)->next;
	return (i);
}

int	casemicolon(char *prompt, int i, t_lst **word)
{
	(*word)->content = ft_calloc(sizeof(char), 2);
	(*word)->content[0] = prompt[i++];
	(*word)->next = ft_calloc(sizeof(t_lst), 1);
	(*word) = (*word)->next;
	return (i);
}

void	tok_pipe(t_mnours *data, t_exec *exec, t_args *pre_tok)
{
	exec->next = ft_calloc(sizeof(t_exec), 1);
	if (!exec->next)
		ft_error("Alloc exec", data);
	free(pre_tok->next);
	pre_tok->next = NULL;
	data->nb_pipe++;
}

void	tok_semicolon(t_mnours *data, t_exec *exec, t_args *pre_tok)
{
	exec->next = ft_calloc(sizeof(t_exec), 1);
	if (!exec->next)
		ft_error("Alloc exec", data);
	free(pre_tok->next);
	pre_tok->next = NULL;
	// Pour les points-virgules, on n'augmente pas nb_pipe car ce ne sont pas des pipes
}

void	set_token(t_mnours *data)
{
	data->ex = ft_calloc(sizeof(t_exec), 1);
	if (!data->ex)
		ft_error("Malloc error", data);
	data->ex->args = ft_calloc(sizeof(t_args), 1);
	if (!data->ex->args)
		ft_error("Malloc error", data);
	tokener(data, data->ex, data->ex->args);
}
