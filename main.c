/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/02/24 11:37:08 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    char *str;
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (cmd == NULL)
        return (1);

    cmd->cmd = NULL;
    cmd->arg = NULL;
    cmd->redirection = NULL;
    cmd->pipe = NULL;
    while (1)
    {
        str = readline("minishell$ ");
        parsing(str, cmd);
        printf("cmd: %s\n", cmd->cmd);
		print_arguments(cmd->arg);
        
        if (cmd->redirection == NULL)
            printf("pas de redirection\n");
        else
        {
            t_redirection *tmp = cmd->redirection;
            while (tmp != NULL)
            {
                printf("type de redirection: %s\n", tmp->type);
                printf("fichier de redirection: %s\n", tmp->file);
                tmp = tmp->next;
            }
        }
        if (cmd->pipe == NULL)
            printf("Pas de pipe\n");
        else
        {
            t_pipe *tmp2 = cmd->pipe;
            while (tmp2 != NULL)
            {
                printf("Pipe : %s\n", tmp2->type);
                tmp2 = tmp2->next;
            }
        }

        free(str);
    }
    
    free(cmd);
    return (0);
}
