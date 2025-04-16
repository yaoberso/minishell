/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:42:39 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/16 10:43:08 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_content_cmd_base(t_cmd *cmd)
{
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
}

void	free_content_cmd_std(t_std *std)
{
	if (std->save_instd >= 0)
	{
		close(std->save_instd);
		std->save_instd = -1;
	}
	if (std->save_outstd >= 0)
	{
		close(std->save_outstd);
		std->save_outstd = -1;
	}
	if (std->original_stdin >= 0)
	{
		close(std->original_stdin);
		std->original_stdin = -1;
	}
}
