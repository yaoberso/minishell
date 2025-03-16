/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:01:37 by nas               #+#    #+#             */
/*   Updated: 2025/03/16 12:26:45 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_token(t_token *token)
{
    t_token *temp;

    while (token)
    {
        temp = token->next;
        if (token->value)
            free(token->value);
        free(token);
        token = temp;
    }
}

void free_redirection(t_redirection *redir)
{
    t_redirection *temp;

    while (redir)
    {
        temp = redir->next;
        if (redir->file)
            free(redir->file);
        if (redir->type)
            free(redir->type);
        if (redir->heredoc_delim)
            free(redir->heredoc_delim);
        free(redir);
        redir = temp;
    }
}

void free_cmd(t_cmd *cmd)
{
    t_cmd *next;

    while (cmd)
    {
        next = cmd->next_cmd;
        if (cmd->arg)
            free_token(cmd->arg);
        if (cmd->cmd)
            free(cmd->cmd);
        if (cmd->redirection)
            free_redirection(cmd->redirection);
        free(cmd);
        cmd = next;
        if (next && next->prev_cmd)
            next->prev_cmd = NULL;
    }
}

