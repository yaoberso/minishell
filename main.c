/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/03/03 12:53:17 by nadahman         ###   ########.fr       */
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
		free(input);
	}
	return (0);
}
