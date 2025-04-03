/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:22:13 by nadahman          #+#    #+#             */
/*   Updated: 2025/04/02 13:46:13 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_pipe_in_exec(t_cmd *cur_cmd, int fd[2], int pipe_precedent)
{
	if (cur_cmd->next_cmd)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			if (pipe_precedent != -1)
				close(pipe_precedent);
			return ;
		}
	}
	else
	{
		fd[1] = -1;
		fd[0] = -1;
	}
}

int	command_not_found(t_cmd *cur_cmd, int pipe_precedent, int fd[2], t_env *env)
{
	char	*cmd_path;

	cmd_path = found_path(cur_cmd, env);
	if (!cmd_path && is_cmd(cur_cmd->cmd) == 0 && cur_cmd->cmd)
	{
		printf("command not found: %s\n", cur_cmd->cmd);
		val_ret = 127;
		if (pipe_precedent != -1)
			close(pipe_precedent);
		if (cur_cmd->next_cmd)
		{
			close(fd[0]);
			close(fd[1]);
		}
		free(cmd_path);
		return (1);
	}
	return (0);
}

void	exit_status_process(int status)
{
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			val_ret = (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			val_ret = 128 + WTERMSIG(status);
		}
	}
}

void	dup_and_close_in_child(t_cmd *cur_cmd, int fd[2], int pipe_precedent)
{
	if (pipe_precedent != -1)
	{
		dup2(pipe_precedent, STDIN_FILENO);
		close(pipe_precedent);
	}
	if (cur_cmd->next_cmd)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
}

void	close_pipes(int fd[2])
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}
