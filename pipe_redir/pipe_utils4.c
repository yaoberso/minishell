/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:31:19 by nas               #+#    #+#             */
/*   Updated: 2025/04/02 11:08:57 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_precedent(int pipe_precedent)
{
	if (pipe_precedent != -1)
		close(pipe_precedent);
}

void	check_fork(pid_t pid, int pipe_precedent, t_cmd *cur_cmd, int fd[2])
{
	if (pid < 0)
	{
		perror("fork");
		if (pipe_precedent != -1)
			close(pipe_precedent);
		if (cur_cmd->next_cmd)
		{
			close(fd[0]);
			close(fd[1]);
		}
		return ;
	}
}

void	exec_simple_cmd(t_cmd *cur_cmd, t_env *env)
{
	int	save_stdin;
	int	save_stdout;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (cur_cmd->redirection && cur_cmd->cmd != NULL
		&& cur_cmd->redirection != NULL)
	{
		exec_redir(cur_cmd);
	}
	cmd_exec(cur_cmd, env);
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdin);
	close(save_stdout);
}

void	child_process(t_cmd *cur_cmd, int fd[2], int pipe_precedent,
		char **envp)
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
	exec_process(cur_cmd, fd, cur_cmd->env, envp);
	exit(1);
}

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
