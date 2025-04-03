/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:22:52 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/03 14:03:59 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	gestion_heredoc(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		val_ret = 130;
		exit(130);
	}
}

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

void	config_signals_exec(void)
{
	struct sigaction	sa;

	sa.sa_handler = gestion_exec;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	config_signals_heredoc()
{
	struct sigaction	sa;

	sa.sa_handler = gestion_heredoc;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}


void	restore_signals(void)
{
	config_signals();
}