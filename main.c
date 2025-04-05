/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/04/05 10:42:47 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include "minishell.h"

// int val_ret = 0;
// t_signal	g_signal = {0, 0};  // Initialisation avec le nouveau champ


// int main(int argc, char **argv, char **envp)
// {
//     char            *input;
//     struct termios  term;
//     t_cmd           *cmd;
//     t_env           *env_list;
//     char            *prompt;

//     (void)argc;
//     (void)argv;
//     env_list = init_env(envp);
//     tcgetattr(STDIN_FILENO, &term);
//     tcsetattr(STDIN_FILENO, TCSANOW, &term);
//     while (1)
//     {   
//         config_signals();
//         prompt = creat_prompt(env_list);
//         input = readline(prompt);
//         free(prompt);
        
//         if (!input)
//         {
//             printf("exit\n");
//             break;
//         }
        
//         if (input[0] == '\0') {
//             free(input);
//             continue;
//         }
//         if (*input)
//             add_history(input);
//         cmd = malloc(sizeof(t_cmd));
//         if (!cmd)
//         {
//             free(input);
//             continue;
//         }
//         ft_memset(cmd, 0, sizeof(t_cmd));
//         cmd->heredoc_fd = -1;
//         parsing(input, cmd, env_list);
//         if (val_ret != 1)
//             exec_pipe(cmd, env_list, envp);
//         free(input);
//         free_cmd(cmd);
//     }
    
//     return (0);
// }


#include "minishell.h"

int val_ret = 0;


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
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// config_signals();
	cmd->cmd = NULL;
    cmd->arg = NULL;
    cmd->redirection = NULL;
    cmd->next_cmd = NULL;
	cmd->prev_cmd = NULL;
	cmd->heredoc_fd = -1;
	while (1)
	{
		config_signals();
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
		if (input[0] == '\0') {
            free(input);
            continue;  // Ignore la commande vide et demande à nouveau une entrée
		}
		if (*input)
			add_history(input);
		parsing(input, cmd, env_list);
		if (val_ret == 1)   // pour eviter d executer une commande et reouvir un prompt, a voir si ca gene ailleurs
        {
            val_ret = 0;
        }
		else
		{	
			exec_pipe(cmd, env_list, envp);
			restore_signals();
		}
		free(input);
		restore_signals();
	}
	return (0);
}