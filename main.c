/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/02/26 10:28:34 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    aff_result(t_cmd *cmd, char *str)
{
    t_redirection *tmp;
    t_cmd *next_cmd;
    
    if (cmd->redirection)
    {
        tmp = cmd->redirection;
        while (tmp != NULL)
        {
            printf("type de redirection: %s\n", tmp->type);
            printf("fichier de redirection: %s\n", tmp->file);
            tmp = tmp->next;
        }
    }
    
    if (cmd->next_cmd)
    {
        next_cmd = cmd->next_cmd;
        while (next_cmd != NULL)
        {
            printf("Pipe : |\n");
            printf("Cmd apres pipe : %s\n", next_cmd->cmd);
            if (next_cmd->arg)
            {
                print_arguments(next_cmd->arg);
            }
            if (next_cmd->redirection)
            {
                printf("Redirections apres pipe :\n");
                tmp = next_cmd->redirection;
                while (tmp != NULL)
                {
                    printf("  Type: %s, Fichier: %s\n", tmp->type, tmp->file);
                    tmp = tmp->next;
                }
            }
            next_cmd = next_cmd->next_cmd;
        }
    }
    free(str);
}

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
    while (1)
    {
        str = readline("minishell$ ");
        parsing(str, cmd);
        printf("cmd: %s\n", cmd->cmd);
		print_arguments(cmd->arg);
        aff_result(cmd, str);
    }
    
    free(cmd);
    return (0);
}
