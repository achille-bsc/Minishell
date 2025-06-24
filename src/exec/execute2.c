/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 23:38:35 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/24 05:28:02 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	access_path(char **cmd, char **env, t_mnours *d)
{
	if (cmd[0] == NULL)
		exit(EXIT_FAILURE);
	if (ft_strchr(cmd[0], '/'))
	{
		signals(SIGNAL_DEFAULT);
		if (execve(cmd[0], cmd, env) == -1)
		{
			signals(SIGNAL_IGN);
			ft_dprintf(2, "%s: Can't open\n", cmd[0]);
			free_mnours(d);
			exit(127);
		}
	}
	else if (cmd[0][0] == '.' && !cmd[0][1])
	{
		ft_dprintf(2, ". can't be alone\n");
		free_mnours(d);
		exit(127);
	}
}

char	*find_path(char *cmop, char **paths)
{
	int		i;
	char	*fpath;
	char	*temp;

	i = 0;
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		fpath = ft_strjoin(temp, cmop);
		free(temp);
		if (access(fpath, X_OK) == 0)
		{
			free_array(paths);
			return (fpath);
		}
		free(fpath);
		i++;
	}
	return (free_array(paths), NULL);
}

void	exec_cmd(char **envp, t_exec *c, t_mnours *mnours)
{
	char	*path;
	char	**tab;

	tab = ft_tabdup(c->lst);
	path = find_path(tab[0], envp);
	if (path == NULL)
	{
		perror("Impossible Path");
		free_array(tab);
		free_mnours(mnours);
		exit(127);
	}
	free_exec(c);
	mnours->ex = NULL;
	signals(SIGNAL_DEFAULT);
	execve(path, tab, mnours->lst_env);
	signals(SIGNAL_IGN);
	perror("Invalid command");
	free_mnours(mnours);
	free(path);
	free_array(tab);
	exit(127);
}

pid_t	child_factory(t_mnours *data, t_exec *c)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close_next_hd(c);
		if (c->fin != 0 && c->is_build == 0)
			dup_close(c->fin, STDIN_FILENO);
		if (c->fout != 1 && c->is_build == 0)
			dup_close(c->fout, STDOUT_FILENO);
		if (c->is_build == 0)
		{
			access_path(c->lst, data->lst_env, data);
			path = "";
			if (get_env(data, "PATH"))
				path = get_env(data, "PATH")->value;
			exec_cmd(ft_split(path, ':'), c, data);
		}
		else
			exec_build(data, c->lst, c);
	}
	return (exec_close_fd(c), pid);
}

void	piping(t_exec *cmd)
{
	int	fd[2];

	if (cmd->next)
	{
		pipe(fd);
		if (cmd->fout == 1)
			cmd->fout = fd[1];
		else
			close(fd[1]);
		if (cmd->next->fin > 2)
			close(fd[0]);
		else
			cmd->next->fin = fd[0];
	}
}
