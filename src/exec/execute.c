/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:33:10 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/08 22:52:45 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <fcntl.h>
#include <unistd.h>

void	access_path(char **cmd, char **env)
{
	if (cmd[0] == NULL)
		exit(EXIT_FAILURE);
	if (strchr(cmd[0], '/'))
	{
		if (access(cmd[0], X_OK) == 0)
		{
			signals(SIGNAL_DEFAULT);
			if (execve(cmd[0], cmd, env) == -1)
			{
				signals(SIGNAL_IGN);
				perror("execve failed\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

char	*find_path(char *cmop, char **envp)
{
	int		i;
	char	**paths;
	char	*fpath;
	char	*temp;

	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		fpath = ft_strjoin(temp, cmop);
		free(temp);
		if (access(fpath, X_OK) == 0)
			return (free_array(paths), fpath);
		free(fpath);
		i++;
	}
	return (free_array(paths), NULL);
}

void	exec_cmd(char **envp, char **cmop, t_mnours *mnours)
{
	char	*path;

	path = find_path(cmop[0], envp);
	if (path == NULL)
	{
		perror("Impossible Path");
		free_mnours(mnours);
		exit(3);
	}
	execve(path, cmop, envp);
	perror("Invailible commande");
	free(path);
}

pid_t	child_factory(t_mnours *data, t_exec *c, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		if (c->fin != 0)
			dup_close(c->fin, STDIN_FILENO);
		if (c->fout != 1)
		{
			if (c->next->fin != 0)
				close(c->next->fin);
			dup_close(c->fout, STDOUT_FILENO);
		}
		if (c->is_build == 0)
		{
			access_path(c->lst, env);
			exec_cmd(env, c->lst, data);
		}
		else
			exec_build(data, c->lst);
	}
	if (c->fin != 0)
		close(c->fin);
	if (c->fout != 1)
		close(c->fout);
	return (pid);
}

void	execute(t_mnours *d, char **env)
{
	int		i;
	int		j;
	int		fd[2];
	t_exec	*cmd;
	pid_t	*pid_stock;
	pid_t	pid;
	int		exit_needs_values[2];

	cmd = d->ex;
	ft_printf("%s\n", cmd->args->name);
	if (d->nb_pipe > 0)
	{
		ft_lstconvert(d, cmd);
		redir(cmd, d);
		i = 0;
		if (d->nb_pipe > 0 || is_buildtin(cmd, cmd->lst[0]) == 0)
			pid_stock = ft_calloc(sizeof(int), d->nb_pipe + 1);
		while (i <= d->nb_pipe)
		{
			if (cmd->fout == 1 && cmd->next)
			{
				redir(cmd->next, d);
				if (cmd->next->fin == 0)
				{
					pipe(fd);
					cmd->fout = fd[1];
					cmd->pipe = OUT;
					cmd->next->fin = fd[0];
					cmd->next->pipe = IN;
				}
			}
			is_buildtin(cmd, cmd->lst[0]);
			if (d->nb_pipe > 0 || cmd->is_build == 0)
				pid_stock[i] = child_factory(d, cmd, env);
			else
				exec_build(d, cmd->lst);
			if (cmd->fout != 1)
				close(cmd->fout);
			if (cmd->fin != 0)
				close(cmd->fin);
			cmd = cmd->next;
			i++;
		}
		if (d->nb_pipe > 0 || d->ex->is_build == 0)
		{
			j = 0;
			while (i-- > 0)
			{
				exit_needs_values[0] = waitpid(pid_stock[j++],
						&exit_needs_values[1], 0);
				if (exit_needs_values[0] == g_signal
					&& WIFEXITED(exit_needs_values[1]))
					d->exit_code = WEXITSTATUS(exit_needs_values[1]);
			}
			free(pid_stock);
		}
	}
	else
	{
		while (cmd)
		{
			ft_lstconvert(d, cmd);
			redir(cmd, d);
			is_buildtin(cmd, cmd->lst[0]);
			if (cmd->is_build == 0)
			{
				pid = child_factory(d, cmd, env);
				waitpid(pid, NULL, 0);
			}
			else
				exec_build(d, cmd->lst);
			cmd = cmd->next;
		}
	}
}
