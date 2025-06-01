/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:25:09 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/01 07:30:34 by abosc            ###   ########.fr       */
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

	// Si le délimiteur commence et finit par des guillemets
	if ((delimiter->name[0] == '\'' && delimiter->name[len - 1] == '\'') ||
		(delimiter->name[0] == '\"' && delimiter->name[len - 1] == '\"'))
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
	char	*expanded_line;
	char	*clean_delimiter;

	close(pipefd[0]);
	signals_heredoc();
	prompt = "> ";
	clean_delimiter = get_clean_delimiter(n);
	while (1)
	{
		line = readline(prompt);
		if (!line)
		{
			ft_printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", clean_delimiter);
			break;
		}
		if (ft_strncmp(line, clean_delimiter, ft_strlen(clean_delimiter)) == 0
			&& ft_strlen(clean_delimiter) == ft_strlen(line))
		{
			free(line);
			break;
		}
		// Expansion des variables uniquement si pas de quotes dans le délimiteur
		if (should_expand_heredoc(n))
		{
			expanded_line = replace_variable(line, mnours->env);
			if (expanded_line)
			{
				write(pipefd[1], expanded_line, ft_strlen(expanded_line));
				free(expanded_line);
			}
			else
			{
				// Si l'expansion échoue, utiliser la ligne originale
				write(pipefd[1], line, ft_strlen(line));
			}
		}
		else
			write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(clean_delimiter);
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
		return;
	}

	signals_ignore_temp();
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		signals_restore();
		return;
	}
	if (pid == 0)
		heredoc2(n, pipefd, mnours);
	else
	{
		close(pipefd[1]);
		c->l_hd = pipefd[0];
		waitpid(pid, &status, 0);
		signals_restore();

		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(pipefd[0]);
			c->l_hd = -1;
			mnours->exit_status = 130;
			return;
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			close(pipefd[0]);
			c->l_hd = -1;
			mnours->exit_status = 130;
			return;
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

void	redir(t_exec *c, t_mnours *mnours)
{
	t_args	*n;

	if (c->fout == 0)
		c->fout = 1;
	n = c->args;
	while (n)
	{
		if (n->tok == HD)
		{
			here_doc(n, c, mnours);
			if (c->l_hd == -1)
				return; // Erreur ou interruption
		}
		n = n->next;
	}
	n = c->args;
	while (n)
	{
		if (n->tok == OP || n->tok == AP || n->tok == TR)
		{
			if (open_file(c, n) == -1)
				return;
		}
		if (n->tok == HD && c->l_hd != -1)
		{
			if (c->fin != -1 && c->fin != 0)
				close(c->fin);
			c->fin = c->l_hd;
			c->l_hd = -1; // Réinitialiser pour éviter les doubles utilisations
		}
		n = n->next;
	}
}

int	should_expand_heredoc(t_args *delimiter)
{
	// Si le délimiteur contient des quotes, ne pas expandre
	// Bash n'expanse que si le délimiteur n'est pas quoté
	if (delimiter->quote == S_Q)
		return (0); // Single quotes : pas d'expansion
	return (1); // Pas de quotes ou double quotes : expansion
}
