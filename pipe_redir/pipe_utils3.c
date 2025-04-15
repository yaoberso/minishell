/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:54:47 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/15 12:57:12 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_process(int *fd, int pipe_precedent, t_cmd *cur_cmd)
{
	close_pipe_precedent(pipe_precedent);
	if (cur_cmd->next_cmd)
	{
		close(fd[1]);
		return (fd[0]);
	}
	return (-1);
}

void	restore_heredoc_stdin(t_cmd *cmd)
{
	if (cmd && cmd->save_stdin >= 0)
	{
		if (dup2(cmd->save_stdin, STDIN_FILENO) == -1)
			perror("dup2 (restore_heredoc_stdin)");
		else
		{
		}
		close(cmd->save_stdin);
		cmd->save_stdin = -1;
	}
}
