/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:51:26 by abosc             #+#    #+#             */
/*   Updated: 2025/06/23 00:35:46 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	capipe(char *prompt, int i, t_lst **word)
{
	(*word)->content = ft_calloc(sizeof(char), 2);
	(*word)->content[0] = prompt[i++];
	(*word)->next = ft_calloc(sizeof(t_lst), 1);
	(*word) = (*word)->next;
	return (i);
}

void	tok_pipe(t_mnours *data, t_exec *exec, t_args *pre_tok)
{
	exec->next = ft_calloc(sizeof(t_exec), 1);
	if (!exec->next)
		ft_error("Alloc exec", data);
	free(pre_tok->next);
	pre_tok->next = NULL;
	data->nb_pipe++;
}

void	tok_semicolon(t_mnours *data, t_exec *exec, t_args *pre_tok)
{
	exec->next = ft_calloc(sizeof(t_exec), 1);
	if (!exec->next)
		ft_error("Alloc exec", data);
	free(pre_tok->next);
	pre_tok->next = NULL;
}

void	expends_status2(t_mnours *mnours, t_args *args)
{
	char	*temp[2];
	int		i;
	char	*str[2];

	i = 0;
	while (args->name[i])
	{
		if (args->name[i] == '$' && args->name[i + 1] == '?')
		{
			str[0] = ft_itoa(mnours->exit_code);
			temp[1] = ft_substr(args->name, 0, i);
			temp[0] = ft_strjoin(temp[1], str[0]);
			free(temp[1]);
			temp[1] = ft_strdup(args->name + i + 2);
			str[1] = ft_strjoin(temp[0], temp[1]);
			free(args->name);
			free(temp[1]);
			free(temp[0]);
			args->name = str[1];
			i += ft_strlen(str[0]);
			free(str[0]);
		}
		else
			i++;
	}
}

void	expends_exit_status(t_mnours *mnours)
{
	t_args	*args;
	t_exec	*exec;
	char	*temp[2];

	exec = mnours->ex;
	while (exec)
	{
		if (exec->args)
		{
			args = exec->args;
			while (args)
			{
				if (args->name)
					expends_status2(mnours, args);
				args = args->next;
			}
		}
		exec = exec->next;
	}
}
