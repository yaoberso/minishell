/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:18:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/02/22 10:14:49 by nas              ###   ########.fr       */
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
    while (1)
    {
        str = readline("minishell$ ");
        parsing(str, cmd);
        printf("cmd: %s\n", cmd->cmd);
		print_arguments(cmd->arg);

        free(str);
    }
    
    free(cmd);
    return (0);
}
