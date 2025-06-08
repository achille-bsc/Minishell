/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:07:30 by abosc             #+#    #+#             */
/*   Updated: 2025/06/07 23:21:55 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	write_args(t_exec *exec)
{
	t_exec	*ex;
	t_args	*arg;

	ex = exec;
	arg = ex->args;
	while (ex)
	{
		ft_printf("--- Exec ---\n");
		while (arg)
		{
			ft_printf("ARG:\n");
			ft_printf("    - Quote: %i\n", arg->quote);
			ft_printf("    - Token: %i\n", arg->tok);
			ft_printf("    - Name:  %s\n", arg->name);
			if (arg->next)
				ft_printf("    - next:  Yes\n");
			else
				ft_printf("    - next:  No\n");
			arg = arg->next;
		}
		ex = ex->next;
		if (!ex)
			return ;
		arg = ex->args;
	}
}

char	*init_prompt(void)
{
	char	*name;
	char	*pwd;
	char	*temp;

	pwd = ft_calloc(sizeof(char), 1024);
	getcwd(pwd, 1024);
	if (!pwd)
		return ("Mininours> ");
	name = getenv("USER");
	temp = ft_strjoin(name, " ");
	temp = ft_strjoin(temp, pwd);
	temp = ft_strjoin(temp, " Mininours> ");
	return (temp);
}

void	prompter(t_mnours *mnours, char **env)
{
	char	stop;
	char	*prompt;

	while (mnours->is_exit == 0)
	{
		signals(SIGNAL_EXECUTE);
		if (mnours->line)
			free(mnours->line);
		prompt = init_prompt();
		mnours->line = readline(prompt);
		signals(SIGNAL_IGN);
		if (g_signal == 130)
		{
			g_signal = 0;
			mnours->exit_code = 130;
		}
		free(prompt);
		if (!mnours->line)
		{
			ft_printf("exit\n");
			mnours->exit = mnours->exit_status;
			mnours->is_exit = 1;
			break ;
		}
		if (!mnours->line[0])
		{
			free(mnours->line);
			mnours->line = NULL;
			continue ;
		}
		add_history(mnours->line);
		if (verif(mnours))
		{
			if (mnours->line != NULL)
				free(mnours->line);
			mnours->line = NULL;
			continue ;
		}
		set_token(mnours);
		execute(mnours, env);
		if (mnours->is_exit == 0)
		{
			free_exec(mnours->ex);
			mnours->ex = NULL;
		}
		g_signal = 0;
	}
	stop = mnours->exit;
	free_mnours(mnours);
	rl_clear_history();
	exit(stop);
}

void	init(t_mnours *mnours, char **env)
{
	mnours->exit_status = 0;
	mnours->prev_status = 0;
	mnours->argc = 0;
	mnours->line = NULL;
	mnours->nb_pipe = 0;
	mnours->ex = NULL;
	mnours->act_exec = 0;
	mnours->pwd = ft_calloc(sizeof(char), 1024);
	getcwd(mnours->pwd, 1024);
	mnours->oldpwd = ft_calloc(sizeof(char), 1024);
	getcwd(mnours->oldpwd, 1024);
	if (!mnours->pwd)
		ft_error("Error: Memory allocation error", mnours);
	set_env(mnours, env);
	mnours->exit = 0;
	mnours->is_exit = 0;
	g_signal = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_mnours	*mininours;

	signals(SIGNAL_IGN);
	(void)argc;
	(void)argv;
	mininours = ft_calloc(sizeof(t_mnours), 1);
	if (!mininours)
		return (ft_error("Error: Memory allocation error", NULL), 1);
	init(mininours, env);
	prompter(mininours, env);
	return (0);
}
