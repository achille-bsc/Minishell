/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:07:30 by abosc             #+#    #+#             */
/*   Updated: 2025/05/27 00:37:36 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	for_an_exec(t_mnours *mnours)
{
	redir(mnours->ex);
}

void	prompter(t_mnours *mnours, char **env)
{
	char	stop;

	while (mnours->is_exit == 0)
	{
		if (mnours->line)
			free(mnours->line);
		mnours->line = readline("Mininours raconte nous une histoire > ");
		add_history(mnours->line);
		verif(mnours);
		set_token(mnours);
		write_args(mnours->ex);
		execute(mnours, env);
		free_exec(mnours->ex);
		mnours->nb_pipe = 0;
	}
	stop = mnours->exit;
	free_mnours(mnours);
	exit(stop);
}

int	main(int argc, char **argv, char **env)
{
	t_mnours	*mininours;

	(void)argc;
	(void)argv;
	mininours = ft_calloc(sizeof(t_mnours), 1);
	if (!mininours)
		return (ft_error("Error: Memory allocation error", NULL), 1);
	prompter(mininours, env);
	return (0);
}

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
