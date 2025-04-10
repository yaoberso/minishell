/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:01:37 by nas               #+#    #+#             */
/*   Updated: 2025/04/10 13:43:57 by nadahman         ###   ########.fr       */
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

void free_content_cmd(t_cmd *cmd)
{
    if (!cmd)
        return;
    
    if (cmd->cmd)
        free(cmd->cmd);
    
    if (cmd->arg)
        free_token(cmd->arg);
    
    if (cmd->redirection)
        free_redirection(cmd->redirection);
    
    if (cmd->next_cmd)
    {
        free_cmd(cmd->next_cmd);
        cmd->next_cmd = NULL;
    }
    
    if (cmd->heredoc_fd >= 0)
    {
        close(cmd->heredoc_fd);
        cmd->heredoc_fd = -1;
    }
    
    if (cmd->save_stdin >= 0)
    {
        close(cmd->save_stdin);
        cmd->save_stdin = -1;
    }
	
    if (cmd->std)
    {
    
        if (cmd->std->save_instd >= 0)
        {
            close(cmd->std->save_instd);
            cmd->std->save_instd = -1;
        }
        
        if (cmd->std->save_outstd >= 0)
        {
            close(cmd->std->save_outstd);
            cmd->std->save_outstd = -1;
        }
        
        if (cmd->std->original_stdin >= 0)
        {
            close(cmd->std->original_stdin);
            cmd->std->original_stdin = -1;
        }
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
        if (cmd->heredoc_fd != -1)
			close(cmd->heredoc_fd);
        if (cmd->std)
            free(cmd->std);
        free(cmd);
        cmd = next;
    }
}

