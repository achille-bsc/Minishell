/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:00:00 by abosc             #+#    #+#             */
/*   Updated: 2025/06/01 09:00:00 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>

/* Variable globale pour gérer les signaux et les processus */
volatile sig_atomic_t g_signal_pid = 0;

void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}

static void	handle_sigint(int code)
{
	(void)code;
	printf("\n");
	clear_rl_line();
	if (g_signal_pid == 0)
		rl_redisplay();
}

static void	handle_sigsegv(int code)
{
	(void)code;
	write(2, "Segmentation fault\n", 19);
	exit(11);
}

static void	handle_sigabrt(int code)
{
	(void)code;
	write(1, "abort\n", 6);
}

void	signals(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGSEGV, &handle_sigsegv);
	signal(SIGABRT, &handle_sigabrt);
	signal(SIGQUIT, SIG_IGN);
}

void	signals2(void)
{
	signal(SIGQUIT, SIG_DFL);
}

/* Fonction pour restaurer les signaux par défaut dans les processus enfants */
void	reset_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
	signal(SIGABRT, SIG_DFL);
}

/* Fonction pour ignorer temporairement les signaux */
void	signals_ignore_temp(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/* Fonction pour restaurer les signaux normaux */
void	signals_restore(void)
{
	signals();
}

/* Fonction pour les signaux dans heredoc */
void	signals_heredoc(void)
{
	/* Dans heredoc, on laisse les signaux par défaut pour que Ctrl+C termine le processus */
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
