/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:24:42 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/15 12:36:12 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_commands(t_cmd *cmd, t_cmd *cur_cmd, t_pipe_data *data)
{
	int	special_case;

	while (cur_cmd)
	{
		create_pipe_in_exec(cur_cmd, data->fd, data->pipe_precedent);
		data->cmd_path = found_path(cur_cmd, data->env);
		special_case = handle_special_cases(cmd, cur_cmd, data);
		if (special_case)
		{
			cur_cmd = cur_cmd->next_cmd;
			continue ;
		}
		execute_fork_command(cmd, cur_cmd, data);
		cur_cmd = cur_cmd->next_cmd;
	}
	cleanup_execution(cmd, data);
}

int	handle_special_cases(t_cmd *cmd, t_cmd *cur_cmd, t_pipe_data *data)
{
	if (command_not_found(cur_cmd, data->pipe_precedent, data->fd, data->env))
	{
		cleanup_command(cmd, data);
		return (1);
	}
	if (is_simple_command(cur_cmd, data))
	{
		exec_simple_cmd(cur_cmd, data->env);
		cleanup_command(cmd, data);
		return (1);
	}
	if (is_builtin_pipe(cur_cmd, data))
	{
		cleanup_builtin(cmd, cur_cmd, data);
		return (1);
	}
	return (0);
}

int	is_simple_command(t_cmd *cur_cmd, t_pipe_data *data)
{
	return (is_cmd(cur_cmd->cmd) && data->pipe_precedent == -1
		&& cur_cmd->next_cmd == NULL);
}

int	is_builtin_pipe(t_cmd *cur_cmd, t_pipe_data *data)
{
	return (cmd_in_pipe(cur_cmd->cmd) && (cur_cmd->next_cmd
			|| data->pipe_precedent != -1));
}

void	cleanup_command(t_cmd *cmd, t_pipe_data *data)
{
	if (data->cmd_path)
		free(data->cmd_path);
	close_pipes(data->fd);
	close_original_stdin_if_needed(cmd, &data->stdin_restored);
	restore_signals();
}
