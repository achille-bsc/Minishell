/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 03:48:28 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/24 03:56:12 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

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
		if (args->tok == HD && args->next && args->next
			&& args->next->tok == PIP)
			return (perror("Syntax error: here-document before pipe"), 1);
		if (args->tok == HD && ft_strlen(args->name) == 0)
			return (perror("Syntax error: here-document without delimiter"), 1);
		exec = exec->next;
	}
	return (0);
}

t_lst	*get_words(char *prompt)
{
	t_lst		*words[2];
	int			i;
	t_quotes	q;

	i = 0;
	q.sin = 0;
	q.dou = 0;
	words[1] = create_word();
	words[0] = words[1];
	while (prompt[i])
	{
		if (!q.sin && !q.dou && (prompt[i] == '<' || prompt[i] == '>'))
			i = handle_redir(prompt, i, &(words[1]));
		else if (!q.sin && !q.dou && prompt[i] == '|')
			i = capipe(prompt, i, &(words[1]));
		else if (!q.sin && !q.dou && (prompt[i] == ' ' || prompt[i] == '\t'))
			while (prompt[i] == ' ' || prompt[i] == '\t')
				i++;
		else
			i = complete(i, prompt, &(words[1]), &q);
	}
	words[1] = words[0];
	get_words2(words[1]);
	return (words[0]);
}
