/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:51:26 by abosc             #+#    #+#             */
/*   Updated: 2025/06/12 00:00:20 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	set_quotes(char prompt, int *in_squote, int *in_dquote)
{
	if (prompt == '\'' && !(*in_dquote))
	{
		*in_squote = !(*in_squote);
	}
	else if (prompt == '\"' && !(*in_squote))
	{
		*in_dquote = !(*in_dquote);
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

int	casemicolon(char *prompt, int i, t_lst **word)
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
	// Pour les points-virgules, on n'augmente pas nb_pipe car ce ne sont pas des pipes
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
					if (!args->name)
					{
						ft_error("Memory allocation error", mnours);
						return ;
					}
				}
				args = args->next;
			}
		}
		exec = exec->next;
	}
}

void	set_token(t_mnours *data)
{
	data->nb_pipe = 0;  // Réinitialiser le nombre de pipes
	data->ex = ft_calloc(sizeof(t_exec), 1);
	if (!data->ex)
		ft_error("Malloc error", data);
	data->ex->args = ft_calloc(sizeof(t_args), 1);
	if (!data->ex->args)
		ft_error("Malloc error", data);
	tokener(data, data->ex, data->ex->args);
	expends_exit_status(data);
}
