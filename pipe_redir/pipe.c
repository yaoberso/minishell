/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:34:51 by nas               #+#    #+#             */
/*   Updated: 2025/04/15 13:12:52 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_original_stdin_if_needed(t_cmd *cmd, int *stdin_restored)
{
	if (!*stdin_restored && cmd->std->original_stdin >= 0)
	{
		dup2(cmd->std->original_stdin, STDIN_FILENO);
		close(cmd->std->original_stdin);
		cmd->std->original_stdin = -1;
		*stdin_restored = 1;
	}
}

void	init_pipe_data(t_pipe_data *data, t_env *env, char **envp)
{
	data->pipe_precedent = -1;
	data->stdin_restored = 0;
	data->heredoc_present = 0;
	data->status = -1;
	data->env = env;
	data->envp = envp;
}

int	process_heredocs(t_cmd *cmd, t_cmd *cur_cmd, t_pipe_data *data)
{
	while (cur_cmd)
	{
		if (cur_cmd->redirection)
		{
			if (exec_heredocs(cur_cmd) == 0)
				data->heredoc_present = 1;
			if (g_val_ret == 130)
			{
				handle_heredoc_interrupt(cmd, cur_cmd, data);
				return (-1);
			}
		}
		cur_cmd = cur_cmd->next_cmd;
	}
	return (0);
}

void	handle_heredoc_interrupt(t_cmd *cmd, t_cmd *cur_cmd, t_pipe_data *data)
{
	if (cur_cmd->save_stdin >= 0)
		close(cur_cmd->save_stdin);
	close_original_stdin_if_needed(cmd, &data->stdin_restored);
}

void	exec_pipe(t_cmd *cmd, t_env *env, char **envp)
{
	t_pipe_data	data;
	t_cmd		*cur_cmd;
	int			result;

	init_pipe_data(&data, env, envp);
	cmd->std->original_stdin = dup(STDIN_FILENO);
	if (cmd->std->original_stdin == -1)
	{
		perror("dup");
		return ;
	}
	cur_cmd = cmd;
	result = process_heredocs(cmd, cur_cmd, &data);
	if (result == -1)
		return ;
	config_signals_exec();
	exec_commands(cmd, cur_cmd, &data);
}
