/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:05:07 by abosc             #+#    #+#             */
/*   Updated: 2025/06/12 01:50:22 by abosc            ###   ########.fr       */
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
		// else if (!in_squote && !in_dquote && prompt[i] == ';')
		// 	i = casemicolon(prompt, i, &(words[1]));
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

int verif_words(t_lst *words, t_mnours *mnours)
{
	t_lst	*tmp;

	if (!words)
		return (0);
	tmp = words;
	while(tmp)
	{
		if (tmp->content[0] == '|' && tmp->next && tmp->next->content[0] == '|')
		{
			ft_error("Syntax error: Double pipe '||' not allowed", mnours);
			return (1);
		}
		if ((tmp->content[0] == '<' || tmp->content[0] == '>') && !tmp->next)
		{
			ft_error("Syntax error: Redirection without command", mnours);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	tokener(t_mnours *mnours, t_exec *exec, t_args *tokens)
{
	t_args	*pre_token;
	t_lst	*words[2];
	// t_exec	*init_exec;

	// init_exec = exec;
	words[1] = get_words(mnours->line);
	if (verif_words(words[1], mnours))
	{
		ft_free_word(words[0]);
		return ;
	}
	;
	t_lst *tmp = words[1];
	while(tmp)
	{
		ft_printf("Word: %s\n", tmp->content);
		tmp = tmp->next;
	}
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
			tokens->name = NULL;
			tokens->next = NULL;
			exec->args = tokens;
		}
		else
			pre_token = and_tok(CMD, &tokens, words[1], 0);
		words[1] = words[1]->next;
	}
	return (ft_free_word(words[0]), pre_token->next = NULL, free(tokens));
}

int	analyze_quote_type(char *str)
{
	int	len;
	int	i;
	int	in_squote;
	int	in_dquote;
	int	has_quotes;

	if (!str || !*str)
		return (NO_Q);

	len = ft_strlen(str);
	i = 0;
	in_squote = 0;
	in_dquote = 0;
	has_quotes = 0;

	// Analyser le string entier pour comprendre le contexte des quotes
	while (i < len)
	{
		if (str[i] == '\'' && !in_dquote)
		{
			in_squote = !in_squote;
			has_quotes = 1;
		}
		else if (str[i] == '\"' && !in_squote)
		{
			in_dquote = !in_dquote;
			has_quotes = 1;
		}
		i++;
	}

	// Si on a des quotes, c'est un token avec quotes (même complexe)
	if (has_quotes)
	{
		// Si le string commence et se termine par des guillemets doubles simples
		if (len >= 2 && str[0] == '\"' && str[len - 1] == '\"')
		{
			// Vérifier s'il n'y a que des guillemets doubles extérieurs
			int j = 1;
			int internal_quotes = 0;
			while (j < len - 1)
			{
				if (str[j] == '\"')
					internal_quotes = 1;
				j++;
			}
			if (!internal_quotes)
				return (D_Q);
		}

		// Si le string commence et se termine par des quotes simples
		if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		{
			// Vérifier qu'il n'y a pas de quotes simples à l'intérieur
			int j = 1;
			while (j < len - 1)
			{
				if (str[j] == '\'')
					return (NO_Q);  // Il y a des quotes simples à l'intérieur
				j++;
			}
			return (S_Q);
		}

		// Cas complexe : retourner NO_Q mais on traitera quand même les quotes
		return (NO_Q);
	}

	return (NO_Q);
}
