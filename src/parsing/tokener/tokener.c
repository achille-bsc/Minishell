/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:05:07 by abosc             #+#    #+#             */
/*   Updated: 2025/06/20 17:59:27 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_lst	*get_words(char *prompt)
{
	t_lst	*words[2];
	int		i;
	int		in_squote;
	int		in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	words[1] = create_word();
	words[0] = words[1];

	while (prompt[i])
	{
		if (!in_squote && !in_dquote && (prompt[i] == '<' || prompt[i] == '>'))
			i = handle_redir(prompt, i, &(words[1]));
		else if (!in_squote && !in_dquote && prompt[i] == '|')
			i = capipe(prompt, i, &(words[1]));
		else if (!in_squote && !in_dquote && (prompt[i] == ' ' || prompt[i] == '\t'))
		{
			while (prompt[i] == ' ' || prompt[i] == '\t')
				i++;
		}
		else
			i = complete(i, prompt, &(words[1]), &in_squote, &in_dquote);
	}
	words[1] = words[0];
	while ((words[1])->next && (words[1])->next->content)
		(words[1]) = words[1]->next;
	if ((words[1])->next)
	{
		free((words[1])->next);
		words[1]->next = NULL;
	}
	return (words[0]);
}

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

int verif_words(t_lst *words)
{
	t_lst	*tmp;

	if (!words)
		return (0);
	tmp = words;
	if (tmp->content[0] == '|')
	{
		perror("Syntax error: Pipe '|' at the beginning of command not allowed");
		return (1);
	}
	while(tmp)
	{
		if (tmp->content[0] == '|' && tmp->next && tmp->next->content[0] == '|')
		{
			perror("Syntax error: Double pipe '| |' not allowed");
			return (1);
		}
		if (tmp->content[0] == '|' && !tmp->next)
		{
			perror("Syntax error: Pipe '|' at the end of command not allowed");
			return (1);
		}
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
		return (ft_free_word(words[1]), 1);
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
			tokens->name = NULL;
			tokens->next = NULL;
			exec->args = tokens;
		}
		else
			pre_token = and_tok(CMD, &tokens, words[1], 0);
		words[1] = words[1]->next;
	}
	return (ft_free_word(words[0]), pre_token->next = NULL, free(tokens), 0);
}

