/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:27:46 by abosc             #+#    #+#             */
/*   Updated: 2025/05/10 00:22:37 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	parsing(t_args *tokens)
{
	t_args	*token;
	int		i;

	i = 0;
	while(token->next)
	{
		if (i == 0 && token->tok == PIP)
		{
			printf("Error: syntax error near unexpected token '|'\n");
			return ;
		}
		if (token->tok == PIP && token->next->tok == PIP)
		{
			printf("Error: syntax error near unexpected token '|'\n");
			return ;
		}

		if (token->tok == CMD && token->next->tok == PIP)
		{
			printf("Error: syntax error near unexpected token '|'\n");
			return ;
		}
		token = token->next;
		i++;
	}
}
