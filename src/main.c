/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:07:30 by abosc             #+#    #+#             */
/*   Updated: 2025/06/01 07:20:30 by abosc            ###   ########.fr       */
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
	char	*temp;

	pwd = ft_calloc(sizeof(char), 1024);
	getcwd(pwd, 1024);
	if (!pwd)
		return ("\033[34mMininours>\033[0m ");
	name = getenv("USER");
	temp = ft_strjoin("\033[32m", name);
	name = ft_strjoin(temp, "\033[0m ");
	free(temp);
	temp = ft_strjoin("\033[33m", pwd);
	free(pwd);
	pwd = ft_strjoin(temp, "\033[0m ");
	free(temp);
	prompt = ft_strjoin(name, pwd);
	temp = ft_strjoin(prompt, "\033[34mMininours>\033[0m ");
	free(prompt);
	free(pwd);
	free(name);
	if (!temp)
		return ("\033[34mMininours>\033[0m ");
	return (temp);
}

void	prompter(t_mnours *mnours, char **env)
{
	char	stop;
	char	*prompt;
	int		signal_status;

	while (mnours->is_exit == 0)
	{
		if (mnours->line)
			free(mnours->line);

		// Vérifier si un signal a été reçu
		signal_status = get_signal_status();
		if (signal_status)
			mnours->exit_status = signal_status;

		prompt = init_prompt();
		mnours->line = readline(prompt);
		free(prompt);

		if (!mnours->line)
		{
			ft_printf("exit\n");
			mnours->is_exit = 1;
			break;
		}

		// Ne pas traiter les lignes vides
		if (!mnours->line[0])
		{
			free(mnours->line);
			mnours->line = NULL;
			continue;
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
