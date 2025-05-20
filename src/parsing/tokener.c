/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:05:07 by abosc             #+#    #+#             */
/*   Updated: 2025/05/20 19:08:17 by alegrix          ###   ########.fr       */
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
			capipe(prompt, i, &(words[1]));
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
			words->content += 2;
			tokens->name = ft_strdup(words->content);
			tokens->quote = NO_Q;
			words->content -= 2;
		}
		else if (words->content[0] == '<')
		{
			tokens->tok = OP;
			words->content++;
			tokens->name = ft_strdup(words->content);
			tokens->quote = NO_Q;
			words->content--;
		}
		else if (words->content[0] == '>' && words->content[1] == '>')
		{
			words->content += 2;
			tokens->tok = AP;
			tokens->name = ft_strdup(words->content);
			tokens->quote = NO_Q;
			words->content -= 2;
		}
		else if (words->content[0] == '>')
		{
			words->content++;
			tokens->tok = TR;
			tokens->name = ft_strdup(words->content);
			tokens->quote = NO_Q;
			words->content--;
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
	check_args(init_exec);
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
