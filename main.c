/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/02/23 19:03:21 by nas              ###   ########.fr       */
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

        free(str);
    }
    
    free(cmd);
    return (0);
}
