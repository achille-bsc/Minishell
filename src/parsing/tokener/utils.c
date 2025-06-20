/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:51:26 by abosc             #+#    #+#             */
/*   Updated: 2025/06/20 19:22:11 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	set_quotes(char prompt, t_quotes *q)
{
	if (prompt == '\'' && !((*q).dou))
	{
		(*q).sin = !((*q).sin);
	}
	else if (prompt == '\"' && !((*q).sin))
	{
		(*q).dou = !((*q).dou);
	}
}

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

void	expends_exit_status(t_mnours *mnours)
{
	t_args	*args;
	t_exec	*exec;

	exec = mnours->ex;
	while (exec)
	{
		if (exec->args)
		{
			args = exec->args;
			while (args)
			{
				if (ft_strncmp(args->name, "$?", 2) == 0
					&& ft_strlen(args->name) == 2)
				{
					free(args->name);
					args->name = ft_itoa(mnours->exit_code);
				}
				args = args->next;
			}
		}
		exec = exec->next;
	}
}

int	set_token(t_mnours *data)
{
	data->nb_pipe = 0;
	data->ex = ft_calloc(sizeof(t_exec), 1);
	if (!data->ex)
		ft_error("Malloc error", data);
	data->ex->args = ft_calloc(sizeof(t_args), 1);
	if (!data->ex->args)
		ft_error("Malloc error", data);
	if (tokener(data, data->ex, data->ex->args) == 1)
		return (1);
	expends_exit_status(data);
	return (0);
}
