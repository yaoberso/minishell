/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:22:52 by yaoberso          #+#    #+#             */
/*   Updated: 2025/03/24 13:20:28 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal g_signal_info;

// Signal handler pour le mode interactif (prompt)
void	gestionnaire(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		val_ret = 130;
	}
}

// Signal handler pour le mode heredoc
void	gestion_heredoc(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "\n", 1);
		val_ret = 130;
		close(g_signal_info.heredoc_fd[0]);
		close(g_signal_info.heredoc_fd[1]);
		exit(130);
	}
}

// Signal handler pour les commandes en exécution
void	gestion_exec(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		val_ret = 130;
	}
	else if (sig == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		val_ret = 131;
	}
}

// Configuration des signaux pour le mode interactif
void	config_signals(void)
{
	struct sigaction	sa;

	g_signal_info.mode = 0; // Mode interactif
	sa.sa_handler = gestionnaire;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

// Configuration des signaux pour le mode d'exécution
void	config_signals_exec(void)
{
	struct sigaction	sa;

	g_signal_info.mode = 1; // Mode exécution
	sa.sa_handler = gestion_exec;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

// Configuration des signaux pour le mode heredoc
void	config_signals_heredoc(int fd[2])
{
	struct sigaction	sa;

	g_signal_info.mode = 2; // Mode heredoc
	g_signal_info.heredoc_fd[0] = fd[0];
	g_signal_info.heredoc_fd[1] = fd[1];
	sa.sa_handler = gestion_heredoc;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

// Restauration des signaux au mode interactif
void	restore_signals(void)
{
	config_signals();
}