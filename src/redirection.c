/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:25:09 by alegrix           #+#    #+#             */
/*   Updated: 2025/04/30 21:44:26 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	resetfd(int fd)
{
	if (fd != 0)
	{
		close(fd);
		fd = 0;
	}
}

int	heredoc2(t_args *n, int pipefd[2])
{
	char	*line;

	close(pipefd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, n->name, ft_strlen(n->name)) == 0
			&& ft_strlen(n->name) == ft_strlen(line) - 1)
		{
			free(line);
			get_next_line(-1);
			close(pipefd[1]);
			exit(0);
		}
		write(pipefd[1], line, ft_strlen(line));
		free (line);
	}
}

void	here_doc(t_args *n, t_exec *c)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	resetfd(c->l_hd);
	if (pipe(pipefd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		heredoc2(n, pipefd);
	else
	{
		close(pipefd[1]);
		c->l_hd = pipefd[0];
		waitpid(pid, &status, 0);
	}
}

int	open_file_in(t_exec *c, t_args *n)
{
	if (n->tok == OP)
	{
		resetfd(c->fin);
		c->fin = open(n->name, O_RDONLY, 0644);
		if (c->fin == -1)
			return (perror("file not found (fderror)"), -1);
	}
	if (c->fin == -1)
		return (perror("fderror"), -1);
	return (1);
}

int	open_file(t_exec *c, t_args *n)
{
	if (n->tok == AP)
	{
		resetfd(c->fout);
		c->fout = open(n->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else if (n->tok == TR)
	{
		resetfd(c->fout);
		c->fout = open(n->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else
		return (open_file_in(c, n));
	if (c->fout == -1)
		return (perror("fderror"), -1);
	return (1);
}

void	redir(t_exec *c)
{
	t_args	*n;
	int		fd[2];

	n = c->args;
	while (n)
	{
		if (n->tok == HD)
			here_doc(n, c);
		n = n->next;
	}
	n = c->args;
	while (n)
	{
		if (n->tok == OP || n->tok == AP || n->tok == TR)
			open_file(c, n);
		if (n->tok == HD)
		{
			close (c->fin);
			c->fin = c->l_hd;
		}
		n = n->next;
	}
}
