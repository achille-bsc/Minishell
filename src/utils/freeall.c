/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:05:16 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/20 03:48:49 by alegrix          ###   ########.fr       */
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
		if (env->name)
			free(env->name);
		if (env->value)
			free(env->value);
		free(env);
		env = temp;
	}
}

void	free_prompt(t_mnours *mnours)
{
	if (mnours->prompt)
	{
		free(mnours->prompt);
		mnours->prompt = NULL;
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
			free_array(exe->lst);
		if (exe->fin > 2)
			close(exe->fin);
		if (exe->fout > 2)
			close(exe->fout);
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
	if (data->oldpwd)
		free(data->oldpwd);
	if (data->env)
		free_env(data->env);
	if (data->ex)
		free_exec(data->ex);
	if (data->lst_env)
		free_array(data->lst_env);
	if (data->pid_stock)
		free(data->pid_stock);
	if (data->prompt)
		free(data->prompt);
	if (data)
		free(data);
}

void	close_fds(int fd)
{
	while (fd < 1024)
		close(fd++);
}
