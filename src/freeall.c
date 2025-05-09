/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:05:16 by alegrix           #+#    #+#             */
/*   Updated: 2025/05/10 00:23:18 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
}

void	ft_error(char *msg, t_mnours *data)
{
	ft_dprintf(2, "%s\n", msg);
	free_mnours(data);
}
