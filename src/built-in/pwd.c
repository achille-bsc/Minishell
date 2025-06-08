/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 07:59:33 by abosc             #+#    #+#             */
/*   Updated: 2025/05/31 08:01:02 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int ft_pwd(t_mnours *mnours)
{
  if (!mnours->pwd)
  {
    ft_error("Error: Unable to get current working directory", mnours);
    return (1);
  }
  ft_printf("%s\n", mnours->pwd);
  return (0);
}
