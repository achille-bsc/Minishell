/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:19:12 by abosc             #+#    #+#             */
/*   Updated: 2025/06/12 00:21:07 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int			g_signal = 0;

static void	int_handler(int sig)
{
	(void)sig;
	ft_dprintf(2, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 130;
}

static void	here_doc_sigint(int sig)
{
	(void)sig;
	ft_dprintf(2, "\n");
	g_signal = 130;
	close_fds(0);
}

void	signals(int sig)
{
	if (sig == SIGNAL_EXECUTE)
	{
		signal(SIGINT, int_handler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGPIPE, SIG_IGN);
	}
	else if (sig == SIGNAL_HERE_DOC)
	{
		signal(SIGINT, here_doc_sigint);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGPIPE, SIG_IGN);
	}
	else if (sig == SIGNAL_DEFAULT)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_DFL);
	}
	else if (sig == SIGNAL_IGN)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGPIPE, SIG_IGN);
	}
}

static void	int_handler_wait(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_dprintf(2, "Quit (core dumped)");
		g_signal = 131;
	}
	else if (sig == SIGINT)
		g_signal = 130;
	ft_dprintf(2, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	signals_wait(void)
{
	signal(SIGINT, int_handler_wait);
	signal(SIGQUIT, int_handler_wait);
	signal(SIGPIPE, SIG_IGN);
}
