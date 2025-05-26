/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:37:38 by abosc             #+#    #+#             */
/*   Updated: 2025/05/27 01:42:14 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_error(char *msg, t_mnours *data)
{
	ft_dprintf(2, "%s\n", msg);
	if (data->nb_pipe > 0)
		free_mnours(data);
	else
		free(data->ex)
}
