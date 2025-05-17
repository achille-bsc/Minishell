/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:07:30 by abosc             #+#    #+#             */
/*   Updated: 2025/05/17 02:17:39 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	for_an_exec(t_mnours *mnours)
{
	redir(mnours->ex);
}

void	prompter(t_mnours *mnours, char **env)
{
	while (mnours->exit == 0)
	{
		if (mnours->line)
			free(mnours->line);
		mnours->line = readline("Mininours raconte nous une histoire > ");
		add_history(mnours->line);
		t_args *test = 	tokener(mnours);
		set_tok_in_mnours(test, mnours);
		execute(mnours, env);
		free_exec(mnours->ex);
	}
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
