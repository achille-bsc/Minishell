/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:07:30 by abosc             #+#    #+#             */
/*   Updated: 2025/05/10 00:53:24 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	prompter(t_mnours *mnours, char **env)
{
	(void)env;
	while (mnours->exit == 0)
	{
		mnours->line = readline("Mininours raconte nous une histoire > ");
		add_history(mnours->line);
		// TODO: Historique a mettre en place
		set_tok_in_mnours(tokener(mnours->line));
		free(mnours->line);
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
