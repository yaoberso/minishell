/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/03/11 13:39:55 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	char			*input;
	struct termios	term;
	t_cmd			*cmd;
	t_env			*env_list;
	char *prompt;

	(void)argc;
    (void)argv;
	env_list = init_env(envp);
	cmd = malloc(sizeof(t_cmd));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	config_signals();
	cmd->cmd = NULL;
    cmd->arg = NULL;
    cmd->redirection = NULL;
    cmd->next_cmd = NULL;
	cmd->prev_cmd = NULL;
	cmd->env = NULL;
	while (1)
	{
        // Créer l'invite en utilisant le chemin courant
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
		exec_cmd_inter_exter(cmd, env_list);
		free(input);
		free(cmd);
	}
	return (0);
}
