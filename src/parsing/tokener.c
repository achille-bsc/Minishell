/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:05:07 by abosc             #+#    #+#             */
/*   Updated: 2025/05/17 02:19:16 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int set_dquote(char prompt, int in_quote)
{
	if (prompt == '"')
		in_quote = !in_quote;
	return (in_quote);
}

t_lst	*get_words(char *prompt)
{
	t_lst	*words;
	t_lst	*init_word;
	int		i;
	int		j;
	int		in_quote;

	i = 0;
	j = 0;
	in_quote = 0;
	words = ft_calloc(sizeof(t_lst), 1);
	words->content = ft_calloc(sizeof(char), ft_strlen(prompt));
	ft_printf("prompt and len : %s et %d\n", prompt, ft_strlen(prompt));
	init_word = words;
	while (prompt[i])
	{
		in_quote = set_dquote(prompt[i], in_quote);
		if (!in_quote && (prompt[i] == '<' || prompt[i] == '>'))
		{
			if (j > 0)
			{
				words->content[j] = '\0';
				words->next = ft_calloc(sizeof(t_lst), 1);
				words = words->next;
				words->content = ft_calloc(sizeof(char), ft_strlen(prompt) + i);
				j = 0;
			}
			i = handle_redir(prompt, i, words->content);
			words->next = ft_calloc(sizeof(t_lst), 1);
			words = words->next;
			words->content = ft_calloc(sizeof(char), ft_strlen(prompt) + i);
			j = 0;
		}
		else if (!in_quote && (prompt[i] == '|' || prompt[i] == ' '))
		{
			if (j > 0)
			{
				words->content[j] = '\0';
				words->next = ft_calloc(sizeof(t_lst), 1);
				words = words->next;
				words->content = ft_calloc(sizeof(char), ft_strlen(prompt) + i);
				j = 0;
			}
			if (prompt[i++] == ' ')
				continue ;
			words->content = ft_calloc(sizeof(char), 1);
			words->content[0] = prompt[i];
			words->next = ft_calloc(sizeof(t_lst), 1);
			words = words->next;
			words->content = ft_calloc(sizeof(char), ft_strlen(prompt) + i);
			j = 0;
		}
		else
		{
			words->content[j] = prompt[i];
			j++;
		}
		i++;
	}
	return (init_word);
}

t_args	*tokener(t_mnours *mnours)
{
	t_lst	*words;
	t_args	*tokens;
	t_args	*init_token;

	words = get_words(mnours->line);
	tokens = ft_calloc(sizeof(t_args), sizeof(mnours->line));
	if (!tokens)
		return (perror("Error: Memory allocation failed"), NULL);
	init_token = tokens;
	while (words)
	{
		ft_printf("words->content %c\n", words->content[0]);
		if (words->content[0] == '<' && words->content[1] == '<')
		{
			tokens->tok = OP; 
			tokens->name = ft_strdup(words->content);
			tokens->quote = NO_Q;
		}
		else if (words->content[0] == '<')
		{
			tokens->tok = HD;
			tokens->name = ft_strdup(words->content);
			tokens->quote = NO_Q;
		}
		else if (words->content[0] == '>' && words->content[1] == '>')
		{
			tokens->tok = AP;
			tokens->name = ft_strdup(words->content);
			tokens->quote = NO_Q;
		}
		else if (words->content[0] == '>')
		{
			tokens->tok = TR;
			tokens->name = ft_strdup(words->content);
			tokens->quote = NO_Q;
			ft_printf("tokens %d et %s\n", tokens->tok, tokens->name);
		}
		else if (words->content[0] == '|')
		{
			mnours->nb_pipe += 1;
			tokens->tok = PIP;
			tokens->name = ft_strdup(words->content);
			tokens->quote = NO_Q;
		}
		else if (words->content[0] == ' ')
		{
			tokens->tok = CMD;
			tokens->name = ft_strdup(words->content);
			tokens->quote = NO_Q;
		}
		else if (words->content[0] == '\'' || words->content[0] == '\"')
		{
			tokens->tok = CMD;
			tokens->name = ft_strdup(words->content);
			if (words->content[0] == '\'')
				tokens->quote = S_Q;
			else
				tokens->quote = D_Q;
		}
		else
		{
			tokens->tok = CMD;
			tokens->name = ft_strdup(words->content);
			tokens->quote = NO_Q;
		}
		words = words->next;
		if (words)
		{
			tokens->next = ft_calloc(sizeof(t_args), sizeof(mnours->line));
			if (!tokens->next)
			{
				perror("Error: Memory allocation failed");
				return (NULL);
			}
			tokens = tokens->next;
		}
	}
	ft_printf("tokens fin enum %d et name %s\n", init_token->tok, init_token->name);
	return (init_token);
}

void news_exec(t_args *tokens, t_exec *exe, t_mnours *mnours)
{
	t_exec	*n_exec;

	n_exec = ft_calloc(sizeof(t_exec), 1);
	if (!n_exec)
		ft_error("malloc error", mnours);
	n_exec->args = tokens->next;
	mnours->ex = n_exec;
	exe = exe->next;
}
void	set_tok_in_mnours(t_args *tokens, t_mnours *mnours)
{
	t_args	*tmp;
	t_exec	*f_exec;
	t_exec	*tmp_exec;

	f_exec = ft_calloc(sizeof(t_exec), 1);
	if (!f_exec)
		ft_error("malloc error", mnours);
	f_exec->args = tokens;
	tmp_exec = f_exec;
	while (tokens)
	{
		if (tokens->tok == PIP)
		{
			tmp = tokens;
			news_exec(tokens, tmp_exec, mnours);
			tmp_exec = tmp_exec->next;
			tokens = tokens->next;
			tmp_exec->args = tokens;
			free(tmp);
		}
		else
		{
			tokens = tokens->next;
		}
	}
	mnours->ex = f_exec;
}
