/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:05:07 by abosc             #+#    #+#             */
/*   Updated: 2025/05/21 00:50:35 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

t_lst	*get_words(char *prompt)
{
	t_lst	*words[2];
	int		i;
	int		in_quote;

	i = 0;
	in_quote = 0;
	words[1] = create_word();
	words[0] = words[1];
	while (prompt[i])
	{
		in_quote = set_dquote(prompt[i], in_quote);
		if (!in_quote && (prompt[i] == '<' || prompt[i] == '>'))
			i = handle_redir(prompt, i, &(words[1]));
		else if (!in_quote && prompt[i] == '|')
			i = capipe(prompt, i, &(words[1]));
		else if (!in_quote && (prompt[i] == ' ' || prompt[i] == '\t'))
			while (prompt[i] == ' ' || prompt[i] == '\t')
				i++;
		else
			i = complete(i, prompt, &(words[1]), &in_quote);
	}
	words[1] = words[0];
	while ((words[1])->next->content)
		(words[1]) = words[1]->next;
	return (free((words[1])->next), words[1]->next = NULL, words[0]);
}

t_args	*and_tok(int en, t_args **token, t_lst *word, int nb_redir)
{
	t_args	*pre_tok;

	(*token)->tok = en;
	word->content += nb_redir;
	(*token)->name = ft_strdup(word->content);
	if ((*token)->name[0] == '\'')
		(*token)->quote = S_Q;
	if ((*token)->name[0] == '\"')
		(*token)->quote = D_Q;
	word->content -= nb_redir;
	(*token)->next = ft_calloc(sizeof(t_args), 1);
	pre_tok = (*token);
	(*token) = (*token)->next;
	return (pre_tok);
}

t_args	*maybe_redir(t_args **token, t_lst *words)
{
	if (words->content[0] == '<' && words->content[1] == '<')
		return (and_tok(HD, token, words, 2));
	else if (words->content[0] == '<')
		return (and_tok(OP, token, words, 1));
	else if (words->content[0] == '>' && words->content[1] == '>')
		return (and_tok(AP, token, words, 2));
	else
		return (and_tok(TR, token, words, 1));
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

void	tokener(t_mnours *mnours, t_exec *exec, t_args *tokens)
{
	t_args	*pre_token;
	t_lst	*words[2];
	t_exec	*init_exec;

	init_exec = exec;
	words[0] = get_words(mnours->line);
	words[1] = words[0];
	while (words[1])
	{
		if (words[1]->content[0] == '<' || words[1]->content[0] == '>')
			pre_token = maybe_redir(&tokens, words[1]);
		else if (words[1]->content[0] == '|')
		{
			tok_pipe(mnours, exec, pre_token);
			exec = exec->next;
			tokens = ft_calloc(sizeof(t_args), 1);
			if (!tokens)
				ft_error("Tokens alloc", mnours);
			exec->args = tokens;
		}
		else
			pre_token = and_tok(CMD, &tokens, words[1], 0);
		words[1] = words[1]->next;
	}
	return (ft_free_word(words[0]), pre_token->next = NULL, free(tokens));
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
