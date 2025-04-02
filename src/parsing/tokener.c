/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:05:07 by abosc             #+#    #+#             */
/*   Updated: 2025/04/02 22:45:34 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_exec	*tokener(char **parsed_prompt)
{
	int		i;
	int		j;
	char	*arg;
	t_exec	*exec;
	t_args	*args;

	i = 0;
	j = 0;
	exec = ft_calloc(sizeof(t_exec), 1);
	while (parsed_prompt[i])
	{
		arg = ft_calloc(sizeof(char), ft_strlen(parsed_prompt[i]));
		while (parsed_prompt[i][j])
		{
			if (parsed_prompt[i][j] == '|' && parsed_prompt[i][j - 1] != '\\')
			{

				arg[j] = '\0';
				args->name = ft_strdup(arg);
				free(arg);
				exec->args = args;
				exec->next = ft_calloc(sizeof(t_exec), 1);
				exec = exec->next;
				args = ft_calloc(sizeof(t_args), 1);
			}
			else if (parsed_prompt[i][j] == '>')
			{
				exec->args = args;
				exec->tok = e_token->TR;
				exec->next = ft_calloc(sizeof(t_exec), 1);
				exec = exec->next;
				args = NULL;
			}
			else if (parsed_prompt[i][j] == '<')
			{
				
				exec->args = args;
				exec->tok = HD;
				exec->next = ft_calloc(sizeof(t_exec), 1);
				exec = exec->next;
				args = NULL;
			}
			else if (parsed_prompt[i][j] == ' ')
			{
				args->next = ft_calloc(sizeof(t_args), 1);
				args = args->next;
			}
			else
			{
				args->name = ft_strjoin(args->name, parsed_prompt[i][j]);
			}
		}
		i++;
	}
}
