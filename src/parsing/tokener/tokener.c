/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:05:07 by abosc             #+#    #+#             */
/*   Updated: 2025/06/11 21:47:20 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

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
		// in_quote = set_dquote(prompt[i], in_quote);
		// ft_printf("in_quote: %i\n", in_quote);
		// ft_printf("prompt[%i]: %c\n", i, prompt[i]);
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
	int		len;

	(*token)->tok = en;
	word->content += nb_redir;
	(*token)->name = ft_strdup(word->content);
	(*token)->quote = NO_Q;
	len = ft_strlen((*token)->name);
	if (len >= 2)
	{
		if ((*token)->name[0] == '\'' && (*token)->name[len - 1] == '\'')
			(*token)->quote = S_Q;
		else if ((*token)->name[0] == '\"' && (*token)->name[len - 1] == '\"')
			(*token)->quote = D_Q;
	}
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

void	tokener(t_mnours *mnours, t_exec *exec, t_args *tokens)
{
	t_args	*pre_token;
	t_lst	*words[2];
	// t_exec	*init_exec;

	// init_exec = exec;
	words[1] = get_words(mnours->line);
	words[0] = words[1];
	// mnours->nb_pipe = 0;
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
		else if (words[1]->content[0] == ';')
		{
			tok_semicolon(mnours, exec, pre_token);
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
