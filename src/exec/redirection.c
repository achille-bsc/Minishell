/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:25:09 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/13 01:40:19 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_clean_delimiter(t_args *delimiter)
{
	char	*clean_delimiter;
	int		len;

	if (!delimiter || !delimiter->name)
		return (NULL);
	len = ft_strlen(delimiter->name);
	if (len < 2)
		return (ft_strdup(delimiter->name));
	if ((delimiter->name[0] == '\'' && delimiter->name[len - 1] == '\'')
		|| (delimiter->name[0] == '\"' && delimiter->name[len - 1] == '\"'))
	{
		clean_delimiter = ft_substr(delimiter->name, 1, len - 2);
		return (clean_delimiter);
	}
	return (ft_strdup(delimiter->name));
}

int	heredoc2(t_args *n, int pipefd[2], t_mnours *mnours)
{
	char	*line;
	char	*prompt;
	char	*clean_delimiter;

	close(pipefd[0]);
	prompt = "> ";
	clean_delimiter = get_clean_delimiter(n);
	while (1)
	{
		signals(SIGNAL_HERE_DOC);
		line = readline(prompt);
		signals(SIGNAL_IGN);
		if (line == NULL)
		{
			ft_dprintf(2, "minishell: warning: here-document "
					"delimited by end-of-file (wanted `%s')\n", clean_delimiter);
			free(clean_delimiter);
			free_mnours(mnours);
			close(pipefd[1]);
			exit(13);
		}
		if (ft_strncmp(line, clean_delimiter, ft_strlen(clean_delimiter)) == 0
			&& ft_strlen(clean_delimiter) == ft_strlen(line))
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(clean_delimiter);
	free_mnours(mnours);
	close(pipefd[1]);
	exit(0);
}

void	here_doc(t_args *n, t_exec *c, t_mnours *mnours)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	resetfd(c->l_hd, 0);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
	}
	else if (pid == 0)
		heredoc2(n, pipefd, mnours);
	else
	{
		close(pipefd[1]);
		c->l_hd = pipefd[0];
		waitpid(pid, &status, 0);
		mnours->exit_code = WEXITSTATUS(status);
		if (mnours->exit_code == 130)
		{
			close(c->l_hd);
			c->l_hd = -1;
		}
	}
}

int	open_file_in(t_exec *c, t_args *n)
{
	if (n->tok == OP)
	{
		resetfd(c->fin, 0);
		c->fin = open(n->name, O_RDONLY, 0644);
		if (c->fin == -1)
		{
			perror(n->name);
			return (-1);
		}
	}
	return (1);
}

int	open_file(t_exec *c, t_args *n)
{
	if (n->tok == AP)
	{
		resetfd(c->fout, 1);
		c->fout = open(n->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (c->fout == -1)
		{
			perror(n->name);
			return (-1);
		}
	}
	else if (n->tok == TR)
	{
		resetfd(c->fout, 1);
		c->fout = open(n->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (c->fout == -1)
		{
			perror(n->name);
			return (-1);
		}
	}
	else
		return (open_file_in(c, n));
	return (1);
}

int	set_heredoc(t_exec *c, t_mnours *data)
{
	t_args	*n;
	t_exec	*tmp;

	tmp = c;
	while (tmp)
	{
		n = tmp->args;
		while (n)
		{
			if (n->tok == HD)
			{
				here_doc(n, tmp, data);
				if (tmp->l_hd == -1)
					return (-1);
			}
			n = n->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	redir(t_exec *c)
{
	t_args	*n;

	if (c->fout == 0)
		c->fout = 1;
	n = c->args;
	while (n)
	{
		if (n->tok == OP || n->tok == AP || n->tok == TR)
		{
			if (open_file(c, n) == -1)
				return (-1);
		}
		if (n->tok == HD)
		{
			if (c->fin > 2 && c->fin != c->l_hd)
				close(c->fin);
			c->fin = c->l_hd;
		}
		n = n->next;
	}
	if (c->l_hd == c->fin)
		c->l_hd = 0;
	if (c->l_hd > 2)
		close(c->l_hd);
	return (1);
}

int	should_expand_heredoc(t_args *delimiter)
{
	if (delimiter->quote == S_Q)
		return (0);
	return (1);
}
