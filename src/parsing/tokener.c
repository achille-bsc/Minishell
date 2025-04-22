/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:05:07 by abosc             #+#    #+#             */
/*   Updated: 2025/04/22 18:53:09 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_list	*get_words(char *prompt)
{
	t_list	*words;
	t_list	*init_word;
	int		i;
	int		in_dquote;
	int		in_squote;

	words = ft_calloc(sizeof(t_list), sizeof(prompt));
	init_word = words;
	while (prompt[i])
	{
		in_dquote = set_dquote(prompt[i], in_dquote);
		in_squote = set_squote(prompt[i], in_squote);
		if (!in_dquote &&  (prompt[i] == '<' || prompt[i] == '>'))
	}
	return (words);
}

t_list	*tokener(char *prompt)
{
	t_list	*words;

	words = get_words(prompt);
	return (words);
}
