/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:26:16 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/15 12:43:23 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_builtin(t_cmd *cmd, t_cmd *cur_cmd, t_pipe_data *data)
{
	if (data->cmd_path)
		free(data->cmd_path);
	close_pipes(data->fd);
	close_original_stdin_if_needed(cmd, &data->stdin_restored);
	if (cur_cmd->save_stdin != -1)
		close(cur_cmd->save_stdin);
}

void	execute_fork_command(t_cmd *cmd, t_cmd *cur_cmd, t_pipe_data *data)
{
	data->pid = fork();
	check_fork(data->pid, data->pipe_precedent, cur_cmd, data->fd);
	if (data->pid == 0)
		execute_child_process(cmd, cur_cmd, data);
	if (data->cmd_path)
		free(data->cmd_path);
	data->pipe_precedent = parent_process(data->fd, data->pipe_precedent,
			cur_cmd);
}

void	execute_child_process(t_cmd *cmd, t_cmd *cur_cmd, t_pipe_data *data)
{
	if (cmd->std->original_stdin >= 0)
		close(cmd->std->original_stdin);
	if (data->cmd_path)
		free(data->cmd_path);
	child_process(cur_cmd, data->fd, data->pipe_precedent, data->envp);
}

void	cleanup_execution(t_cmd *cmd, t_pipe_data *data)
{
	close_pipe_precedent(data->pipe_precedent);
	exit_status_process(data->status);
	close_pipes(data->fd);
	close_original_stdin_if_needed(cmd, &data->stdin_restored);
	if (data->heredoc_present)
		close_all_heredoc_fds(cmd);
	restore_signals();
}

void	close_all_heredoc_fds(t_cmd *cmd)
{
	t_cmd	*cur_cmd;

	cur_cmd = cmd;
	while (cur_cmd)
	{
		if (cur_cmd->save_stdin != -1)
			close(cur_cmd->save_stdin);
		cur_cmd = cur_cmd->next_cmd;
	}
}
