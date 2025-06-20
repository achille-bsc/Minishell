/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:00:39 by abosc             #+#    #+#             */
/*   Updated: 2025/06/20 18:01:17 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
