/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:55:55 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/10 23:26:51 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_buildtin(t_exec *exe, char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)) && ft_strlen(cmd) == 4)
		return (exe->is_build = 1, 1);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)) && ft_strlen(cmd) == 2)
		return (exe->is_build = 1, 1);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)) && ft_strlen(cmd) == 6)
		return (exe->is_build = 1, 1);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)) && ft_strlen(cmd) == 5)
		return (exe->is_build = 1, 1);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)) && ft_strlen(cmd) == 3)
		return (exe->is_build = 1, 1);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)) && ft_strlen(cmd) == 4)
		return (exe->is_build = 1, 1);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)) && ft_strlen(cmd) == 3)
		return (exe->is_build = 1, 1);
	else
		return (0);
}

void	exec_build(t_mnours *data, char **l)
{
	if (!ft_strncmp(l[0], "echo", ft_strlen(l[0])) && ft_strlen(l[0]) == 4)
		ft_echo(l);
//	else if (!ft_strncmp(l[0], "cd", ft_strlen(l[0])) && ft_strlen(l[0]) == 2)
		//ft_cd();
	else if (!ft_strncmp(l[0], "export", ft_strlen(l[0]))
		&& ft_strlen(l[0]) == 6)
		ft_export(data, data->env, l);
	else if (!ft_strncmp(l[0], "unset", ft_strlen(l[0]))
		&& ft_strlen(l[0]) == 5)
		data->env = ft_unset(data->env, l, data);
	else if (!ft_strncmp(l[0], "env", ft_strlen(l[0])) && ft_strlen(l[0]) == 3)
		ft_env(data->lst_env);
	else if (!ft_strncmp(l[0], "exit", ft_strlen(l[0])) && ft_strlen(l[0]) == 4)
		ft_exit(data, l);

	else if (!ft_strncmp(l[0], "pwd", ft_strlen(l[0])) && ft_strlen(l[0]) == 3)
		ft_pwd (data);
	else if (!ft_strncmp(l[0], "cd", ft_strlen(l[0])) && ft_strlen(l[0]) == 2)
		ft_cd(l, data);
	if (data->nb_pipe > 0)
	{
		free_mnours(data);
		exit(0);
	}
}
