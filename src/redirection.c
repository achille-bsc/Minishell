/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:25:09 by alegrix           #+#    #+#             */
/*   Updated: 2025/03/09 02:28:24 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	heredoc(t_args *n)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		exit(-1);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, n->name, ft_strlen(n->name)) == 0
			&& ft_strlen(n->name) == ft_strlen(line) - 1)
		{
			free(line);
			get_next_line(-1);
			close(pipefd[1]);
			return (pipefd[0]);
		}
		write(pipefd[1], line, ft_strlen(line));
		free (line);
	}
}

int	open_file_in(t_exec *c, t_args *n)
{
	if (n->tok == OP)
	{
		if (c->fin != 0)
			close(c->fin);
		c->fin = open(n->name, O_RDONLY, 0644);
		if (c->fin == -1)
			return (perror("file not found (fderror)"), -1);
	}
	else
	{
		if (c->fin != 0)
			close(c->fin);
		c->fin = heredoc(n);
	}
	if (c->fin == -1)
		return (perror("fderror"), -1);
	return (1);
}

int	open_file(t_exec *c, t_args *n)
{
	if (n->tok == AP)
	{
		if (c->fout != 0)
			close(c->fout);
		c->fout = open(n->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else if (n->tok == TR)
	{
		if (c->fout != 0)
			close(c->fout);
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

	n = c->args;
	while (n)
	{
		if (n->tok == OP || n->tok == HD || n->tok == AP || n->tok == TR)
			open_file(c, n);
		n = n->next;
	}
}
