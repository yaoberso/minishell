/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:22:52 by yaoberso          #+#    #+#             */
/*   Updated: 2025/03/25 12:28:09 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>



void gestionnaire(int sig)
{
	if (sig == SIGINT) // CTRL+C
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		val_ret = 130;
	}
}


// void gestion_heredoc(int sig, int heredoc_fd[2])
// {
// 	if (sig == SIGINT || sig == SIGQUIT) // CTRL+C ou CTRL+
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		val_ret = 130;
// 		close(heredoc_fd[0]);
// 		close(heredoc_fd[1]);
// 		exit(130);
// 	}
// }


// void gestion_exec(int sig)
// {
// 	if (sig == SIGINT) // CTRL+C
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		val_ret = 130;
// 	}
// 	else if (sig == SIGQUIT) // CTRL+
// 	{
// 		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
// 		val_ret = 131;
// 	}
// }


// void config_signals(void)
// {
// 	struct sigaction sa;

// 	sa.sa_handler = gestionnaire;
// 	sa.sa_flags = 0;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// 	sa.sa_handler = SIG_IGN; // Ignorer SIGQUIT
// 	sigaction(SIGQUIT, &sa, NULL);
// }

// void config_signals_exec(void)
// {
// 	struct sigaction sa;

// 	sa.sa_handler = gestion_exec;
// 	sa.sa_flags = 0;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// }


// void config_signals_heredoc(int heredoc_fd[2])
// {
//     struct sigaction sa;
//     static t_signal signal; 

//     signal.heredoc_fd[0] = heredoc_fd[0];
//     signal.heredoc_fd[1] = heredoc_fd[1];

//     sa.sa_flags = SA_SIGINFO;
//     sa.sa_sigaction = gestion_heredoc;
//     sigemptyset(&sa.sa_mask);
//     sigaction(SIGINT, &sa, NULL);
//     sigaction(SIGQUIT, &sa, NULL);
// }


// void restore_signals(void)
// {
// 	config_signals();
// }
