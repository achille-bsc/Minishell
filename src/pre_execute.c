/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:55:55 by alegrix           #+#    #+#             */
/*   Updated: 2025/05/21 01:18:36 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_buildtin(t_exec *exe, char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) && ft_strlen(cmd) == 4)
		return (exe->is_build = 1, 1);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) && ft_strlen(cmd) == 2)
		return (exe->is_build = 1, 1);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) && ft_strlen(cmd) == 6)
		return (exe->is_build = 1, 1);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) && ft_strlen(cmd) == 5)
		return (exe->is_build = 1, 1);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) && ft_strlen(cmd) == 3)
		return (exe->is_build = 1, 1);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) && ft_strlen(cmd) == 4)
		return (exe->is_build = 1, 1);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) && ft_strlen(cmd) == 3)
		return (exe->is_build = 1, 1);
	else
		return (0);
}

void	exec_build()
