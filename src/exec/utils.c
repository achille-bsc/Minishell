/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:32:34 by abosc             #+#    #+#             */
/*   Updated: 2025/06/23 23:44:51 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	close_next_hd(t_exec *c)
{
	t_exec	*tmp;

	tmp = c->next;
	while (tmp)
	{
		if (tmp->l_hd > 2)
			close(tmp->l_hd);
		tmp = tmp->next;
	}
}

void	exec_close_fd(t_exec *cmd)
{
	if (cmd->fout > 2)
		close(cmd->fout);
	if (cmd->fin > 2)
		close(cmd->fin);
}

void	dup_close(int fd, int fileno)
{
	dup2(fd, fileno);
	close(fd);
}

void	resetfd(int fd, int fout)
{
	if (fout == 0 && fd > 2)
	{
		close(fd);
		fd = 0;
	}
	if (fout == 1 && fd > 2)
	{
		close(fd);
		fd = 1;
	}
}
