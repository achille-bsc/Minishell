/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 07:59:33 by abosc             #+#    #+#             */
/*   Updated: 2025/06/12 15:06:19 by alegrix          ###   ########.fr       */
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
	if (ft_printf("%s\n", mnours->pwd) != (int)ft_strlen(mnours->pwd))
		ft_dprintf(2, "Outfile is full\n");
	return (0);
}
