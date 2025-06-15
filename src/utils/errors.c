/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:37:38 by abosc             #+#    #+#             */
/*   Updated: 2025/06/15 07:04:48 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_error(char *msg, t_mnours *data)
{
	ft_dprintf(2, "%s\n", msg);
	free_exec(data->ex);
	free(data->line);
	data->line = NULL;
}
