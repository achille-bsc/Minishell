/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:33:10 by alegrix           #+#    #+#             */
/*   Updated: 2025/03/14 00:09:34 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <fcntl.h>

void	free_array(char **array)
{
	int	index;

	if (!array)
		return ;
	index = 0;
	while (array[index])
		free(array[index++]);
	free(array);
	return ;
}

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

pid_t	child_factory(t_exec *c, char **env)
{
	pid_t	pid;
	t_args	*tmp;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		tmp = c->args;
		dup2(c->fin, STDIN_FILENO);
		close(c->fin);
		dup2(c->fout, STDOUT_FILENO);
		close(c->fout);
		while (tmp->tok != CMD && tmp)
			tmp = tmp->next;
		access_path(tmp->args, env);
		exec_cmd(env, tmp->args);
	}
	dup2(c->fout, STDOUT_FILENO);
	close(c->fout);
	dup2(c->fin, STDIN_FILENO);
	return (close(c->fin), pid);
}

void	execute(t_mnours *d, char **env)
{
	int		i;
	int		j;
	int		fd[2];
	t_exec	*cmd;
	pid_t	*pid_stock;

	cmd = d->ex;
	i = 0;
	pid_stock = ft_calloc(sizeof(int), d->nb_pipe);
	while (i < d->nb_pipe)
	{
		if (cmd->fout == 0 && cmd->next)
		{
			if (cmd->next->fin == 0)
			{
				pipe(fd);
				cmd->fout = fd[1];
				cmd->next->fin = fd[0];
			}
		}
		pid_stock[i++] = child_factory(cmd, env);
		cmd = cmd->next;
	}
	j = 0;
	while (i-- > 0)
		waitpid(pid_stock[j++], NULL, 0);
	free(pid_stock);
}

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
	d->ex->args->args = ft_calloc(sizeof(char *), 3);
	d->ex->args->args[0] = ft_strdup("cat");
	d->ex->args->args[1] = ft_strdup("-e");
	d->ex->args->args[2] = NULL;
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
	tmp->args->args = ft_calloc(sizeof(char *), 3);
	tmp->args->args[0] = ft_strdup("cat");
	tmp->args->args[1] = ft_strdup("-e");
	tmp->args->args[2] = NULL;
	execute(d, env);
	free(tmp->args->args[2]);
	free(tmp->args->args[1]);
	free(tmp->args->args[0]);
	free(tmp->args);
	free(tmp);
	free(d);
}
