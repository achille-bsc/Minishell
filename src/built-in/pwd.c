/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 07:59:33 by abosc             #+#    #+#             */
/*   Updated: 2025/06/12 22:16:06 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(t_mnours *mnours)
{
	if (!mnours->pwd)
	{
		ft_error("Error: Unable to get current working directory", mnours);
		return (1);
	}
	if (write(1, mnours->pwd, (int)ft_strlen(mnours->pwd)) == -1)
		ft_dprintf(2, "Outfile is full\n");
	write(1, "\n", 1);
	return (0);
}
