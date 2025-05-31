/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:07:30 by abosc             #+#    #+#             */
/*   Updated: 2025/05/31 02:19:08 by abosc            ###   ########.fr       */
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
	char	*prompt;
	char	*name;
	char	*pwd;

	pwd = ft_calloc(sizeof(char), 1024);
	getcwd(pwd, 1024);
	if (!pwd)
		return ("\033[34mMininours>\033[0m ");
	name = getenv("USER");
	name = ft_strjoin("\033[32m", name);
	name = ft_strjoin(name, "\033[0m ");
	pwd = ft_strjoin("\033[33m", pwd);
	pwd = ft_strjoin(pwd, "\033[0m ");
	prompt = ft_strjoin(name, pwd);
	prompt = ft_strjoin(prompt, "\033[34mMininours>\033[0m ");
	free(pwd);
	free(name);
	if (!prompt)
		return ("\033[34mMininours>\033[0m ");
	return (prompt);
}

void	prompter(t_mnours *mnours, char **env)
{
	char	stop;

	while (mnours->is_exit == 0)
	{
		if (mnours->line)
			free(mnours->line);
		mnours->line = readline(init_prompt());
		if (!mnours->line)
		{
			ft_printf("exit\n");
			free_mnours(mnours);
			mnours->is_exit = 1;
		}
		add_history(mnours->line);
		if (verif(mnours))
			continue ;
		set_token(mnours);
		execute(mnours, env);
		if (mnours->is_exit == 0)
			free_exec(mnours->ex);
	}
	stop = mnours->exit;
	free_mnours(mnours);
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
	ft_printf("path: %s\n", mnours->pwd);
	if (!mnours->pwd)
		ft_error("Error: Memory allocation error", mnours);
	set_env(mnours, env);
	mnours->exit = 0;
	mnours->is_exit = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_mnours	*mininours;

	(void)argc;
	(void)argv;
	signals();
	mininours = ft_calloc(sizeof(t_mnours), 1);
	if (!mininours)
		return (ft_error("Error: Memory allocation error", NULL), 1);
	init(mininours, env);
	prompter(mininours, env);
	return (0);
}
