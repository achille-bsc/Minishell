/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:05:16 by alegrix           #+#    #+#             */
/*   Updated: 2025/05/27 01:39:32 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_free_word(t_lst *word)
{
	t_lst	*tmp;

	tmp = word;
	while (word)
	{
		tmp = word;
		word = word->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = temp;
	}
}

void	free_args(t_args *args)
{
	t_args	*temp;

	while (args)
	{
		temp = (args)->next;
		if (args->name)
			free(args->name);
		free(args);
		args = temp;
	}
}

void	free_exec(t_exec *exe)
{
	t_exec	*temp;

	while (exe)
	{
		temp = exe->next;
		if (exe->args)
			free_args(exe->args);
		if (exe->lst)
			free(exe->lst);
		free(exe);
		exe = temp;
	}
}

void	free_mnours(t_mnours *data)
{
	if (data->line)
		free(data->line);
	if (data->pwd)
		free(data->pwd);
	if (data->env)
		free_env(data->env);
	if (data->ex)
		free_exec(data->ex);
	free(data);
}
