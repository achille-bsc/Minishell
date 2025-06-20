/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:00:39 by abosc             #+#    #+#             */
/*   Updated: 2025/06/20 19:39:23 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
