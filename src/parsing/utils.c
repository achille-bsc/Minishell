/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:47:05 by abosc             #+#    #+#             */
/*   Updated: 2025/04/22 22:38:34 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	set_quote(char c, int in_quote)
{
	if (in_quote == 0 && c == '\'')
		in_quote = 1;
	else if (in_quote == 1 && c == '\'')
		in_quote = 0;
	if (in_quote == 0 && c == '\"')
		in_quote = 2;
	else if (in_quote == 2 && c == '\"')
		in_quote = 0;
	return (in_quote);
}
int	handle_redir(char *prompt, int i, char *word)
{	
	word = ft_calloc(sizeof(char), 2);
	word[0] = prompt[i];
	if (prompt[i + 1] == prompt[i])
	{
		word[1] = prompt[i];
		i++;
	}
	else
		word[1] = '\0';
	return (i);
}
