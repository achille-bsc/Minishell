/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:07:30 by abosc             #+#    #+#             */
/*   Updated: 2025/04/30 23:38:47 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	prompter(t_mnours *mnours, char **env)
{
	while (truc = 0)
	{
		mnours->line = readline("Mininours raconte nous une histoire > ");
		// TODO: Historique a mettre en place
		tokener(mnours->line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mnours	*mininours;
	
	mininours = ft_calloc(sizeof(t_mnours), 1);
	if (!mininours)
		return (ft_error("Error: Memory allocation error", NULL), 1);
	
	prompter(mininours, env);
	return (0);
}

