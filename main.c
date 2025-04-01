/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/04/01 12:48:09 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	val_ret = 0;

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	struct termios	term;
	t_cmd			*cmd;
	t_env			*env_list;
	char			*prompt;

	(void)argc;
	(void)argv;
	env_list = init_env(envp);
	cmd = malloc(sizeof(t_cmd));
	tcgetattr(STDIN_FILENO, &term);
	// term.c_lflag &= ~ECHOCTL;   // ca ici qui n affiche pas les ^C
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	config_signals();
	cmd->cmd = NULL;
	cmd->arg = NULL;
	cmd->redirection = NULL;
	cmd->next_cmd = NULL;
	cmd->prev_cmd = NULL;
	cmd->heredoc_fd = -1;
	while (1)
	{
		prompt = creat_prompt(env_list);
		input = readline(prompt);
		free(prompt);
		if (!input)
		{
			free(cmd);
			free_env(env_list);
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		parsing(input, cmd, env_list);
		if (val_ret == 1)
		{
			val_ret = 0;
		}
		else
		{
			exec_pipe(cmd, env_list, envp);
			restore_signals();
		}
		free(input);
	}
	return (0);
}
