/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:33:10 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/23 00:43:00 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	execute5(t_mnours *d, t_exec *cmd, char **env)
{
	int	exit_val;
	int	pid;

	is_buildtin(cmd, cmd->lst[0]);
	if (cmd->is_build == 0)
	{
		pid = child_factory(d, cmd, env);
		waitpid(pid, &exit_val, 0);
		if (WCOREDUMP(exit_val)
			&& WIFSIGNALED(exit_val) && WTERMSIG(exit_val) == SIGQUIT)
		{
			ft_dprintf(2, "Quit (core dumped)\n");
			d->exit_code = 131;
		}
		else if (WIFSIGNALED(exit_val) && WTERMSIG(exit_val) == SIGINT)
		{
			ft_dprintf(2, "\n");
			d->exit_code = 130;
		}
		else
			d->exit_code = WEXITSTATUS(exit_val);
	}
	else
		exec_build(d, cmd->lst, cmd);
}

int	execute4(t_mnours *d, int i)
{
	int	exit_val[2];
	int	j;

	j = 0;
	while (i-- > 0)
	{
		if (d->pid_stock[j++])
		{
			signals_wait();
			exit_val[0] = waitpid(d->pid_stock[j - 1], &exit_val[1], 0);
			if (WCOREDUMP(exit_val[1]) && WIFSIGNALED(exit_val[1])
				&& WTERMSIG(exit_val[1]) == SIGQUIT)
				return (d->exit_code = 131, ft_dprintf(2,
						"Quit (core dumped)\n"));
			if (WIFSIGNALED(exit_val[1])
				&& WTERMSIG(exit_val[1]) == SIGINT)
				return (d->exit_code = 130, ft_dprintf(2, "\n"));
			else
				d->exit_code = WEXITSTATUS(exit_val[1]);
		}
	}
	return (0);
}

int	execute3(t_exec **cmd, int bool)
{
	if (bool == 0)
		piping(*cmd);
	if ((*cmd)->fout > 2)
		close((*cmd)->fout);
	if ((*cmd)->fin > 2 && bool == 0)
		close((*cmd)->fin);
	*cmd = (*cmd)->next;
	return (1);
}

int	execute2(t_mnours *d, t_exec *cmd, char **env)
{
	int	i;

	i = 0;
	while (i <= d->nb_pipe && cmd->lst)
	{
		if (redir(cmd, d) == -1)
		{
			i += execute3(&cmd, 0);
			continue ;
		}
		piping(cmd);
		if (cmd->lst[0] == NULL || cmd->lst[0][0] == '\0')
		{
			i += execute3(&cmd, 1);
			continue ;
		}
		is_buildtin(cmd, cmd->lst[0]);
		if (d->nb_pipe > 0 || cmd->is_build == 0)
			d->pid_stock[i++] = child_factory(d, cmd, env);
		else
			exec_build(d, cmd->lst, cmd);
		exec_close_fd(cmd);
		cmd = cmd->next;
	}
	return (i);
}

void	execute(t_mnours *d, char **env)
{
	int		i;
	t_exec	*cmd;

	cmd = d->ex;
	if (set_heredoc(d->ex, d) == -1)
		return ;
	d->pid_stock = ft_calloc(sizeof(int), d->nb_pipe + 1);
	ft_lstconvert(d, cmd);
	if (d->nb_pipe > 0)
	{
		i = execute2(d, cmd, env);
		if (d->nb_pipe > 0 || d->ex->is_build == 0)
			execute4(d, i);
	}
	else
	{
		if (redir(cmd, d) != -1)
			if (cmd->lst[0])
				execute5(d, cmd, env);
		exec_close_fd(cmd);
	}
}
