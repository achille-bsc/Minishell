/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:51:26 by abosc             #+#    #+#             */
/*   Updated: 2025/06/22 23:44:19 by abosc            ###   ########.fr       */
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

void	expends_exit_status(t_mnours *mnours)
{
	t_args	*args;
	t_exec	*exec;
	int		i;
	char	*new_str;
	char	*exit_code_str;
	char	*before;
	char	*after;
	char	*temp;

	exec = mnours->ex;
	while (exec)
	{
		if (exec->args)
		{
			args = exec->args;
			while (args)
			{
				if (args->name)
				{
					i = 0;
					while (args->name[i])
					{
						if (args->name[i] == '$' && args->name[i + 1] == '?')
						{
							exit_code_str = ft_itoa(mnours->exit_code);
							before = ft_substr(args->name, 0, i);
							after = ft_strdup(args->name + i + 2);
							temp = ft_strjoin(before, exit_code_str);
							new_str = ft_strjoin(temp, after);
							free(args->name);
							free(before);
							free(after);
							free(temp);
							args->name = new_str;
							i += ft_strlen(exit_code_str);
							free(exit_code_str);
						}
						else
							i++;
					}
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
