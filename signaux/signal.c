/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:22:52 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/03 12:19:54 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// Signal handler pour le mode interactif (prompt)
void	gestionnaire(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);    // c est ici que ca affiche le deuxieme prompt a chaque fois
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		val_ret = 130;
	}
}

void gestion_heredoc(int sig)
{
    if (sig == SIGINT)
    {
        // Ne pas appeler exit() ici, cela cause des problèmes avec les descripteurs
        write(STDOUT_FILENO, "\n", 1);
        val_ret = 130;
        // Signaler l'interruption mais laisser le processus terminer naturellement
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

void config_signals_heredoc(void)
{
    struct sigaction sa;
    
    sa.sa_handler = SIG_DFL;  // Comportement par défaut pour SIGINT
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    
    sa.sa_handler = SIG_IGN;  // Ignorer SIGQUIT
    sigaction(SIGQUIT, &sa, NULL);
}

// Restauration des signaux au mode interactif
void	restore_signals(void)
{
	config_signals();

	// rl_on_new_line();
    // rl_replace_line("", 0);
}