/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:05:07 by abosc             #+#    #+#             */
/*   Updated: 2025/06/24 00:57:04 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_args	*and_tok(int en, t_args **token, t_lst *word, int nb_redir)
{
	t_args	*pre_tok;

	(*token)->tok = en;
	word->content += nb_redir;
	(*token)->name = ft_strdup(word->content);
	(*token)->quote = analyze_quote_type((*token)->name);
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

int	verif_words(t_lst *words)
{
	t_lst	*tmp;

	if (!words)
		return (0);
	tmp = words;
	if (tmp->content[0] == '|')
		return (perror("Syntax error:  near unexpected token `|'"), 1);
	while (tmp)
	{
		if (tmp->content[0] == '|' && tmp->next && tmp->next->content[0] == '|')
			return (perror("Syntax error: Double pipe '| |' not allowed"), 1);
		if (tmp->content[0] == '|' && !tmp->next)
			return (perror("Syntax error: Pipe '|' "
							"at the end of command not allowed"),
					1);
		if (tmp->content[0] == '>' && !tmp->content[1] && tmp->next
			&& tmp->next->content[0] == '|')
			return (perror("Syntax error:  near unexpected token `|'"), 1);
		if ((tmp->content[0] == '>' && !tmp->content[1])
			|| (tmp->content[0] == '<' && !tmp->content[1]))
			return (perror("Syntax error: near unexpected token `newline'"), 1);
		tmp = tmp->next;
	}
	return (0);
}

int	tokener(t_mnours *mnours, t_exec *exec, t_args *tokens)
{
	t_args	*pre_token;
	t_lst	*words[2];

	words[1] = get_words(mnours->line);
	if (verif_words(words[1]))
		return (ft_free_word(words[1]), mnours->exit_code = 2, 1);
	words[0] = words[1];
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
	return (ft_free_word(words[0]), pre_token->next = NULL, free(tokens), 0);
}

int	checker(t_exec *exec)
{
	t_args	*args;

	while (exec)
	{
		args = exec->args;
		if (!args || !args->name)
			return (perror("Syntax error: empty command"), 1);
		if (args->tok == OP && args->next && args->next->tok != CMD)
			return (perror("Syntax error: redirection without command"), 1);
		if (args->tok == AP && args->next && args->next->tok != CMD)
			return (perror("Syntax error: append without command"), 1);
		if (args->tok == TR && args->next && args->next->tok != CMD)
			return (perror("Syntax error: truncate without command"), 1);
		if (args->tok == HD && args->next && args->next && args->next->tok == PIP)
			return (perror("Syntax error: here-document before pipe"), 1);
		exec = exec->next;
	}
	return (0);
}

int	set_token(t_mnours *data)
{
	data->nb_pipe = 0;
	data->ex = ft_calloc(sizeof(t_exec), 1);
	if (!data->ex)
		ft_error("Malloc error", data);
	data->ex->args = ft_calloc(sizeof(t_args), 1);
	if (!data->ex->args)
		ft_error("Malloc error", data);
	if (tokener(data, data->ex, data->ex->args) == 1)
		return (1);
	if (checker(data->ex) == 1)
		return (1);
	expends_exit_status(data);
	return (0);
}
