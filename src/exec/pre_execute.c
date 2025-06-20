/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:55:55 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/20 17:49:10 by abosc            ###   ########.fr       */
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

void	exec_build(t_mnours *data, char **l, t_exec *c)
{
	int		fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	if (c->fin != 0)
		dup_close(c->fin, STDIN_FILENO);
	if (c->fout != 1)
		dup_close(c->fout, STDOUT_FILENO);
	if (!ft_strncmp(l[0], "echo", ft_strlen(l[0])) && ft_strlen(l[0]) == 4)
		data->exit_code = ft_echo(l);
	else if (!ft_strncmp(l[0], "export", ft_strlen(l[0]))
		&& ft_strlen(l[0]) == 6)
		data->exit_code = ft_export(data, data->env, l);
	else if (!ft_strncmp(l[0], "unset", ft_strlen(l[0]))
		&& ft_strlen(l[0]) == 5)
		data->env = ft_unset(data->env, l, data);
	else if (!ft_strncmp(l[0], "env", ft_strlen(l[0])) && ft_strlen(l[0]) == 3)
		data->exit_code = ft_env(data->lst_env);
	else if (!ft_strncmp(l[0], "exit", ft_strlen(l[0])) && ft_strlen(l[0]) == 4)
		data->exit_code = ft_exit(data, l);
	else if (!ft_strncmp(l[0], "pwd", ft_strlen(l[0])) && ft_strlen(l[0]) == 3)
		data->exit_code = ft_pwd (data);
	else if (!ft_strncmp(l[0], "cd", ft_strlen(l[0])) && ft_strlen(l[0]) == 2)
		data->exit_code = ft_cd(l, data);
	dup_close(fd[0], STDIN_FILENO);
	dup_close(fd[1], STDOUT_FILENO);
	if (data->nb_pipe > 0)
	{
		if (c->next && c->next->fout != 1)
			close(c->next->fout);
		if (c->next && c->next->fin != 0)
			close(c->next->fin);
		free_mnours(data);
		exit(0);
	}
}
