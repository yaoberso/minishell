/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:14:01 by nas               #+#    #+#             */
/*   Updated: 2025/04/16 10:38:57 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Signal handler pour le mode interactif (prompt)
void	gestionnaire(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_val_ret = 130;
	}
}

// Signal handler pour le mode heredoc
void	gestion_heredoc(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		close(STDIN_FILENO);
	}
}

// Signal handler pour les commandes en exécution
void	gestion_exec(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_val_ret = 130;
	}
	else if (sig == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		g_val_ret = 131;
	}
}

// Configuration des signaux pour le mode interactif
void	config_signals(void)
{
	struct sigaction	sa;

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

	sa.sa_handler = gestion_exec;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
