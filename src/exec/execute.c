/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:33:10 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/10 21:35:00 by abosc            ###   ########.fr       */
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

char	*find_path(char *cmop, char **paths)
{
	int		i;
	char	*fpath;
	char	*temp;

	// i = 0;
	// while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
	// 	i++;
	// if (envp[i] == NULL)
		// return (NULL);
	// paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		fpath = ft_strjoin(temp, cmop);
		free(temp);
		ft_printf("|||||||||||||||||||%s\n", fpath);
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

void	exec_cmd(char **envp, char **cmop, t_mnours *mnours)
{
	char	*path;
	ft_printf("%s\n", envp[0]);
	path = find_path(cmop[0], envp);
	ft_printf("4sd4f65s46f4sd65%s\n", path);
	if (path == NULL)
	{
		perror("Impossible Path");
		free_mnours(mnours);
		exit(3);
	}
	free_array(envp);
	execve(path, cmop, convert_env(mnours));
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
			exec_cmd(ft_split(get_env(data, "PATH")->value, ':'), c->lst, data);
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
