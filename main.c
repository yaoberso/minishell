/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/04/04 11:32:33 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int val_ret = 0;
t_signal	g_signal = {0, 0};  // Initialisation avec le nouveau champ


int main(int argc, char **argv, char **envp)
{
    char            *input;
    struct termios  term;
    t_cmd           *cmd;
    t_env           *env_list;
    char            *prompt;

    (void)argc;
    (void)argv;
    env_list = init_env(envp);
    tcgetattr(STDIN_FILENO, &term);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    while (1)
    {   
        config_signals();
        prompt = creat_prompt(env_list);
        input = readline(prompt);
        free(prompt);
        
        if (!input)
        {
            printf("exit\n");
            break;
        }
        
        if (input[0] == '\0') {
            free(input);
            continue;
        }
        if (*input)
            add_history(input);
        cmd = malloc(sizeof(t_cmd));
        if (!cmd)
        {
            free(input);
            continue;
        }
        ft_memset(cmd, 0, sizeof(t_cmd));
        cmd->heredoc_fd = -1;
        parsing(input, cmd, env_list);
        if (val_ret != 1)
            exec_pipe(cmd, env_list, envp);
        free(input);
        free_cmd(cmd);
    }
    
    return (0);
}