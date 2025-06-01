/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:33:10 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/01 07:20:30 by abosc            ###   ########.fr       */
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
			if (execve(cmd[0], cmd, env) == -1)
			{
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

void	exec_cmd(char **envp, char **cmop)
{
	char	*path;

	path = find_path(cmop[0], envp);
	if (path == NULL)
	{
		perror("Impossible Path");
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
		reset_signals_child();
		if (c->fin != 0)
			dup_close(c->fin, STDIN_FILENO);
		if (c->fout != 1)
			dup_close(c->fout, STDOUT_FILENO);
		if (c->is_build == 0)
		{
			access_path(c->lst, env);
			exec_cmd(env, c->lst);
		}
		else
			exec_build(data, c->lst);
	}
	// Fermer les descripteurs dans le processus parent
	if (c->pipe == IN && c->fin != 0)
		close(c->fin);
	if (c->pipe == OUT && c->fout != 1)
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

	cmd = d->ex;

	// Si on a des pipes, on traite comme avant
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
			// Fermer les descripteurs de pipe dans le processus parent
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
			signals_ignore_temp();
			while (i-- > 0)
				waitpid(pid_stock[j++], NULL, 0);
			signals_restore();
			free(pid_stock);
		}
	}
	else
	{
		// Pour les commandes séparées par ';' ou commandes simples
		while (cmd)
		{
			ft_lstconvert(d, cmd);
			redir(cmd, d);
			is_buildtin(cmd, cmd->lst[0]);
			if (cmd->is_build == 0)
			{
				pid_t pid = child_factory(d, cmd, env);
				signals_ignore_temp();
				waitpid(pid, NULL, 0);
				signals_restore();
			}
			else
				exec_build(d, cmd->lst);
			cmd = cmd->next;
		}
	}
}

/*
int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_mnours	*d;
	t_exec		*tmp;

	d = malloc(sizeof(t_mnours) * 1);
	if (!d)
		return (0);
	d->ex = ft_calloc(sizeof(t_exec), 1);
	if (!(d->ex))
		return (0);
	d->ex->fin = open("main.c", O_RDONLY, 0644);
	d->ex->args = ft_calloc(sizeof(t_args), 1);
	if (!(d->ex->args))
		return (0);
	d->ex->args->tok = CMD;
	d->ex->args->name = ft_calloc(sizeof(char *), 3);
	d->ex->args->name[0] = ft_strdup("cat");
	d->ex->args->name[1] = ft_strdup("-e");
	d->ex->args->name[2] = NULL;
	d->ex->next = ft_calloc(sizeof(t_exec), 1);
	tmp = d->ex->next;
	if (!(tmp))
		return (0);
	tmp->fin = open("redirection.c", O_RDONLY, 0644);
	tmp->fout = open("Test", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	tmp->args = ft_calloc(sizeof(t_args), 1);
	if (!(d->ex->args))
		return (0);
	tmp->args->tok = CMD;
	d->nb_pipe = 2;
	tmp->args->name = ft_calloc(sizeof(char *), 3);
	tmp->args->name[0] = ft_strdup("cat");
	tmp->args->name[1] = ft_strdup("-e");
	tmp->args->name[2] = NULL;
	execute(d, env);
	free(tmp->args->name[2]);
	free(tmp->args->name[1]);
	free(tmp->args->name[0]);
	free(tmp->args);
	free(tmp);
	free(d);
}*/
