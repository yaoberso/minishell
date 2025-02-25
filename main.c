/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/02/25 12:13:29 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    aff_result(t_cmd *cmd, char *str)
{
    t_redirection *tmp;
    t_pipe *tmp2;
    
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
    if (cmd->pipe)
    {
        tmp2 = cmd->pipe;
        while (tmp2 != NULL)
        {
            printf("Pipe : %s\n", tmp2->type);
            printf("CMD du pipe : %s\n", tmp2->cmd_pipe);
            tmp2 = tmp2->next;
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
    cmd->pipe = NULL;
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
