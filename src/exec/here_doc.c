/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:25:09 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/20 19:39:18 by alegrix          ###   ########.fr       */
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

void	heredoc3(char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		signals(SIGNAL_HERE_DOC);
		line = readline("> ");
		signals(SIGNAL_IGN);
		if (line == NULL)
		{
			ft_dprintf(2, "minishell: warning: here-document delimited"
				" by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(delimiter) == ft_strlen(line))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	heredoc2(t_args *n, int pipefd[2], t_mnours *mnours)
{
	char	*clean_delimiter;

	close(pipefd[0]);
	clean_delimiter = get_clean_delimiter(n);
	heredoc3(clean_delimiter, pipefd[1]);
	free(clean_delimiter);
	free_mnours(mnours);
	close(pipefd[1]);
	exit(g_signal);
}

void	here_doc(t_args *n, t_exec *c, t_mnours *mnours)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	resetfd(c->l_hd, 0);
	if (pipe(pipefd) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid == -1)
		return (close(pipefd[0]), close(pipefd[1]), perror("fork"));
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
