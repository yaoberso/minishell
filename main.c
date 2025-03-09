/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/03/09 16:09:21 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	char			*input;
	struct termios	term;
	t_cmd			*cmd;
	t_env			*env_list;
	char cwd[1024];
	char *prompt;

	(void)argc;
    (void)argv;
	env_list = init_env(envp);
	cmd = malloc(sizeof(t_cmd));
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
		prompt = creat_prompt(cwd);
        input = readline(prompt);
		free(prompt);
		if (!input)
		{
			printf("exit\n");
			break;
		}
		
		if (*input)
		{
			add_history(input);
			parsing(input, cmd);
			exec_pipe(cmd, env_list);
			cmd_exec(cmd, env_list);
			free(input);
		}
	return (0);
}
