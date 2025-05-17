/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:05:07 by abosc             #+#    #+#             */
/*   Updated: 2025/05/17 20:43:23 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	set_dquote(char prompt, int in_quote)
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
			ft_printf("\n\n\nin_quote: %i\nprompt[%i]: \"%c\"\n\n\n", in_quote,
				i, prompt[i]);
			if (j > 0)
			{
				words->content[j] = '\0';
				words->next = ft_calloc(sizeof(t_lst), 1);
				words = words->next;
				words->content = ft_calloc(sizeof(char), ft_strlen(prompt) - i);
				j = 0;
			}
			if (prompt[i] == '|')
			{
				words->content = ft_calloc(sizeof(char), 1);
				words->content[0] = prompt[i];
				ft_printf("word content: %s", words->content);
				words->next = ft_calloc(sizeof(t_lst), 1);
				words = words->next;
				words->content = ft_calloc(sizeof(char), ft_strlen(prompt) - i);
				j = 0;
			}
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

t_exec	*tokener(t_mnours *mnours)
{
	t_lst	*words;
	t_args	*tokens;
	t_args	*init_token;
	t_exec	*exec;
	t_exec	*init_exec;

	exec = ft_calloc(sizeof(t_exec), 1);
	init_exec = exec;
	words = get_words(mnours->line);
	tokens = ft_calloc(sizeof(t_args), sizeof(mnours->line));
	if (!tokens)
		return (perror("Error: Memory allocation failed"), NULL);
	init_token = tokens;
	while (words)
	{
		ft_printf("words->content %s\n", words->content);
		if (words->content[0] == '<' && words->content[1] == '<')
		{
			tokens->tok = HD;
			tokens->name = ft_strdup(words->content);
			tokens->quote = NO_Q;
		}
		else if (words->content[0] == '<')
		{
			tokens->tok = OP;
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
			exec->args = init_token;
			exec->next = ft_calloc(sizeof(t_exec), 1);
			exec = exec->next;
			tokens = ft_calloc(sizeof(t_args), 1);
			init_token = tokens;
			mnours->nb_pipe += 1;
			words = words->next;
			continue ;
			// write_args(mnours);
		}
		// else if (words->content[0] == ' ')
		// {
		// 	tokens->tok = CMD;
		// 	tokens->name = ft_strdup(words->content);
		// 	tokens->quote = NO_Q;
		// }
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
			if (!(words->content[0] == '|'))
			{
				tokens->next = ft_calloc(sizeof(t_args), 1);
				if (!tokens->next)
				{
					perror("Error: Memory allocation failed");
					return (NULL);
				}
				tokens = tokens->next;
			}
		}
	}
	ft_printf("tokens fin enum %d et name %s\n", init_token->tok,
		init_token->name);
	exec->args = init_token;
	return (init_exec);
}

void	news_exec(t_args *tokens, t_exec *exe, t_mnours *mnours)
{
	t_exec	*n_exec;

	n_exec = ft_calloc(sizeof(t_exec), 1);
	if (!n_exec)
		ft_error("malloc error", mnours);
	n_exec->args = tokens->next;
	mnours->ex = n_exec;
	exe = exe->next;
}
