/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:05:23 by abosc             #+#    #+#             */
/*   Updated: 2025/06/01 07:56:05 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef SA_RESTART
#define SA_RESTART 0
#endif

volatile sig_atomic_t g_signal_received = 0;

static void sigint_handler(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void sigquit_handler(int sig)
{
	(void)sig;
	/* En mode interactif, SIGQUIT est ignoré (aucun affichage ni action) */
	/* Bash ignore complètement Ctrl+\ en mode interactif */
}

static void sigint_heredoc_handler(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void signals(void)
{
	struct sigaction sa_int, sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = sigquit_handler;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void signals_heredoc(void)
{
	struct sigaction sa_int, sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = sigint_heredoc_handler;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void reset_signals_child(void)
{
	struct sigaction sa_int, sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = SIG_DFL;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_DFL;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void signals_ignore_temp(void)
{
	struct sigaction sa_int, sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = SIG_IGN;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void signals_restore(void)
{
	struct sigaction sa_int, sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = sigquit_handler;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

int get_signal_status(void)
{
	int status = g_signal_received;
	if (status == SIGINT)
	{
		g_signal_received = 0;
		return (130);
	}
	return (0);
}


// TODO: Correct ctrl+\ handling
