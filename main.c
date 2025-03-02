/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/02/28 13:12:32 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char			*input;
	struct termios	term;
	t_cmd			*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (1);
	cmd->cmd = NULL;
	cmd->arg = NULL;
	cmd->redirection = NULL;
	cmd->next_cmd = NULL;
	cmd->prev_cmd = NULL;
	
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	config_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		
		if (*input)
		{
			add_history(input);
    		parsing(input, cmd);
    		exec_pipe(cmd);
		}
			
		printf("Vous avez tapé : %s\n", input);
		free(input);
	}
	return (0);
}
