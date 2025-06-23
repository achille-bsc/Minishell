/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 01:16:52 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/23 18:34:08 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*init_prompt(t_mnours *mnours)
{
	char	*name;
	char	*pwd;
	char	*temp;
	char	*temp1;

	pwd = ft_calloc(sizeof(char), 1024);
	if (!pwd || !getcwd(pwd, 1024))
	{
		if (pwd)
			free(pwd);
		return (ft_strdup("Mininours> "));
	}
	name = ft_getenv("USER", mnours->env);
	if (name == NULL)
	{
		free(pwd);
		return (ft_strdup("Mininours> "));
	}
	temp = ft_strjoin(name, " ");
	temp1 = ft_strjoin(temp, pwd);
	free(temp);
	temp = ft_strjoin(temp1, " Mininours> ");
	free(temp1);
	free(pwd);
	return (temp);
}

void	prompter3(t_mnours *mnours)
{
	ft_dprintf(2, "exit\n");
	mnours->exit = mnours->exit_status;
	mnours->is_exit = 1;
	free_prompt(mnours);
}

void	prompter2(t_mnours *mnours)
{
	if (!mnours->line[0])
		return (free_prompt(mnours));
	add_history(mnours->line);
	if (verif(mnours))
		return (free_prompt(mnours));
	if (set_token(mnours))
	{
		if (mnours->line)
			free(mnours->line);
		mnours->line = NULL;
		if (mnours->ex)
			free_exec(mnours->ex);
		mnours->ex = NULL;
		return (free_prompt(mnours));
	}
	execute(mnours);
	free_exec(mnours->ex);
	free(mnours->pid_stock);
	mnours->pid_stock = NULL;
	mnours->ex = NULL;
	g_signal = 0;
	free_prompt(mnours);
}

void	prompter(t_mnours *mnours)
{
	char	stop;

	while (mnours->is_exit == 0)
	{
		signals(SIGNAL_EXECUTE);
		if (mnours->line)
			free(mnours->line);
		mnours->prompt = init_prompt(mnours);
		mnours->line = readline(mnours->prompt);
		signals(SIGNAL_IGN);
		if (g_signal == 130)
		{
			g_signal = 0;
			mnours->exit_code = 130;
		}
		if (!mnours->line)
		{
			prompter3(mnours);
			break ;
		}
		prompter2(mnours);
	}
	stop = mnours->exit_code;
	return (free_mnours(mnours), rl_clear_history(), exit(stop));
}
