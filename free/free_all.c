/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:01:37 by nas               #+#    #+#             */
/*   Updated: 2025/04/16 10:42:30 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token->next;
		if (token->value)
			free(token->value);
		free(token);
		token = temp;
	}
}

void	free_redirection(t_redirection *redir)
{
	t_redirection	*temp;

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

void	free_content_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_content_cmd_base(cmd);
	if (cmd->std)
		free_content_cmd_std(cmd->std);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*next;

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

void	free_all(t_cmd *cmd, t_env *env_list)
{
	free_content_cmd(cmd);
	if (cmd->std)
		free(cmd->std);
	free(cmd);
	free_env(env_list);
}
