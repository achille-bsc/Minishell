/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:07:30 by abosc             #+#    #+#             */
/*   Updated: 2025/03/08 00:49:05 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char **argv, char **env)
{
	mininours(argc, argv, env);
	return (0);
}

void	minimours(int argc, char **argv, char **env)
{
	t_main	*datas;

	datas->argc = argc;
	datas->argv = argv;
	datas->env = env;
	parser();
}
