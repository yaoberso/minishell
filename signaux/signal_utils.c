/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:37:39 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/16 10:39:23 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Configuration des signaux pour le mode heredoc
void	config_signals_heredoc(void)
{
	struct sigaction	sa;

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
