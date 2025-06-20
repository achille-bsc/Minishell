/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:33:10 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/20 17:40:51 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <fcntl.h>
#include <unistd.h>

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
			exit(EXIT_FAILURE);
		}
	}
	else if (cmd[0][0] == '.' && !cmd[0][1])
	{
		ft_dprintf(2, ". can't be alone\n");
		free_mnours(d);
		exit(EXIT_FAILURE);
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

pid_t	child_factory(t_mnours *data, t_exec *c, char **env)
{
	pid_t	pid;
	char	*path;
	char	**tmp;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		if (c->next && c->next->l_hd > 2)
			close(c->next->l_hd);
		if (c->fin != 0 && c->is_build == 0)
			dup_close(c->fin, STDIN_FILENO);
		if (c->fout != 1 && c->is_build == 0)
			dup_close(c->fout, STDOUT_FILENO);
		if (c->is_build == 0)
		{
			access_path(c->lst, env, data);
			if (get_env(data, "PATH"))
				path = get_env(data, "PATH")->value;
			else
				path = "";
			tmp = ft_split(path, ':');
			exec_cmd(tmp, c, data);
		}
		else
			exec_build(data, c->lst, c);
	}
	if (c->fin > 2)
		close(c->fin);
	if (c->fout > 2)
		close(c->fout);
	return (pid);
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

void	execute(t_mnours *d, char **env)
{
	int		i;
	int		j;
	t_exec	*cmd;
	pid_t	pid;
	int		exit_needs_values[2];

	cmd = d->ex;
	if (set_heredoc(d->ex, d) == -1)
		return ;
	d->pid_stock = ft_calloc(sizeof(int), d->nb_pipe + 1);
	ft_lstconvert(d, cmd);
	if (d->nb_pipe > 0)
	{
		i = 0;
		while (i <= d->nb_pipe && cmd->lst)
		{
			if (redir(cmd) == -1)
			{
				i++;
				piping(cmd);
				if (cmd->fout > 2)
					close(cmd->fout);
				cmd = cmd->next;
				continue ;
			}
			piping(cmd);
			if (cmd->lst[0] == NULL || cmd->lst[0][0] == '\0')
			{
				if (cmd->fout > 2)
					close(cmd->fout);
				if (cmd->fin > 2)
					close(cmd->fin);
				cmd = cmd->next;
				i++;
				continue ;
			}
			is_buildtin(cmd, cmd->lst[0]);
			if (d->nb_pipe > 0 || cmd->is_build == 0)
				d->pid_stock[i++] = child_factory(d, cmd, env);
			else
				exec_build(d, cmd->lst, cmd);
			if (cmd->fout > 2)
				close(cmd->fout);
			if (cmd->fin > 2)
				close(cmd->fin);
			cmd = cmd->next;
		}
		if (d->nb_pipe > 0 || d->ex->is_build == 0)
		{
			j = 0;
			while (i-- > 0)
			{
				if (d->pid_stock[j++])
				{
					signals_wait();
					exit_needs_values[0] = waitpid(d->pid_stock[j - 1],
							&exit_needs_values[1], 0);
					if (WCOREDUMP(exit_needs_values[1])
						&& WIFSIGNALED(exit_needs_values[1])
						&& WTERMSIG(exit_needs_values[1]) == SIGQUIT)
					{
						ft_dprintf(2, "Quit (core dumped)\n");
						d->exit_code = 131;
						break ;
					}
					if (WIFSIGNALED(exit_needs_values[1])
						&& WTERMSIG(exit_needs_values[1]) == SIGINT)
					{
						ft_dprintf(2, "\n");
						d->exit_code = 130;
						break ;
					}
					else
						d->exit_code = WEXITSTATUS(exit_needs_values[1]);
				}
			}
		}
	}
	else
	{
		if (redir(cmd) != -1)
		{
			if (cmd->lst[0])
			{
				is_buildtin(cmd, cmd->lst[0]);
				if (cmd->is_build == 0)
				{
					pid = child_factory(d, cmd, env);
					waitpid(pid, &exit_needs_values[0], 0);
					if (WCOREDUMP(exit_needs_values[0])
						&& WIFSIGNALED(exit_needs_values[0])
						&& WTERMSIG(exit_needs_values[0]) == SIGQUIT)
					{
						ft_dprintf(2, "Quit (core dumped)\n");
						d->exit_code = 131;
					}
					else if (WIFSIGNALED(exit_needs_values[0])
						&& WTERMSIG(exit_needs_values[0]) == SIGINT)
					{
						ft_dprintf(2, "\n");
						d->exit_code = 130;
					}
					else 
						d->exit_code = WEXITSTATUS(exit_needs_values[0]);
				}
				else
					exec_build(d, cmd->lst, cmd);
			}
		}
		if (cmd->fout > 2)
			close(cmd->fout);
		if (cmd->fin > 2)
			close(cmd->fin);
	}
}
