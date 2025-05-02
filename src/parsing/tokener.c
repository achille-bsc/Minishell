/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:05:07 by abosc             #+#    #+#             */
/*   Updated: 2025/04/26 21:37:32 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_lst	*get_words(char *prompt)
{
	t_lst	*words;
	t_lst	*init_word;
	int		i;
	int		j;
	int		in_quote;

	i = 0;
	words = ft_calloc(sizeof(t_lst), sizeof(prompt));
	init_word = words;
	while (prompt[i])
	{
		in_quote = set_dquote(prompt[i], in_quote);
		if (!in_quote && (prompt[i] == '<' || prompt[i] == '>'))
		{
			if (j > 0)
			{
				words->content[j] = '\0';
				words->next = ft_calloc(sizeof(t_lst), sizeof(prompt + i));
				words = words->next;
				j = 0;
			}
			i = handle_redir(prompt, i, words->content);
			words->next = ft_calloc(sizeof(t_lst), sizeof(prompt + i));
			words = words->next;
			j = 0;
		}
		else if (!in_quote && (prompt[i] == '|' || prompt[i] == ' '))
		{
			if (j > 0)
			{
				words->content[j] = '\0';
				words->next = ft_calloc(sizeof(t_lst), sizeof(prompt + i));
				words = words->next;
				j = 0;
			}
			if (prompt[i++] == ' ')
				continue;
			words->content = ft_calloc(sizeof(char), sizeof(1));
			words->content[0] = prompt[i];
			words->next = ft_calloc(sizeof(t_lst), sizeof(prompt + i));
			words = words->next;
			j = 0;
		}
		else
		{
			words->content[j] = prompt[i];
			j++;
		}
	}
	return (init_word);
}

t_args	*tokener(char *prompt)
{
	t_lst	*words;
	t_args	*tokens;

	words = get_words(prompt);
	tokens = ft_calloc(sizeof(t_args), sizeof(prompt));
	if (!words)
		return (perror("Error: Memory allocation failed"), NULL);
	while (words->next)
	{
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
		}
		else if (words->content[0] == '|')
		{
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
		tokens->next = ft_calloc(sizeof(t_args), sizeof(prompt));
		if (!tokens->next)
		{
			perror("Error: Memory allocation failed");
			return (NULL);
		}
		tokens = tokens->next;
	}
	
	return (tokens);
}
