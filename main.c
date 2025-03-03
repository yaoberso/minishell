/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/03/03 12:20:14 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char			*input;
	struct termios	term;
	t_cmd			*cmd;
	char cwd[1024];
	

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
		if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("getcwd");
            exit(1);
        }

        // Créer l'invite en utilisant le chemin courant
        input = readline(cwd); // Utiliser cwd pour afficher le répertoire courant
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
