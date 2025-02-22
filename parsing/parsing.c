/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:27:05 by nas               #+#    #+#             */
/*   Updated: 2025/02/22 10:13:32 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// regroupe les fonctions de parsing
void parsing(char *str, t_cmd *cmd)
{
    int i;
    char *token;
    int token_count;

	i = 0;
	token_count = 0;
    cmd->cmd = NULL;
    cmd->arg = NULL;

    while ((token = recup_token(str, &i)) != NULL)
    {
        if (token_count == 0)
            cmd->cmd = token;
        else
            add_token(&cmd->arg, new_token(token));

        token_count++;
    }
    if (token_count == 1)
        pars_one_arg(str, cmd);
    else                
        pars_mult(str, cmd);
}

// le cas ou il y'a un seul argument entre guillemets
void pars_one_arg(char *str, t_cmd *cmd)
{
    int i = 0;
    char *token;

    token = recup_token(str, &i);
    if (token != NULL)
    {
        cmd->cmd = token;
        cmd->arg = NULL;
        token = recup_token(str, &i);
        while (token != NULL)
        {
            add_token(&cmd->arg, new_token(token));
            free(token);
            token = recup_token(str, &i);
        }
    }
    else
    {
        cmd->cmd = NULL;
        cmd->arg = NULL;
    }
}

// le cas ou il y'a plusieurs arguments
void pars_mult(char *str, t_cmd *cmd)
{
    int i = 0;
    char *token;

    cmd->arg = NULL;
    cmd->cmd = recup_token(str, &i);

    while ((token = recup_token(str, &i)) != NULL)
    {
        add_token(&cmd->arg, new_token(token));
        free(token);
    }
}

