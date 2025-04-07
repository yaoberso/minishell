/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:31:19 by nas               #+#    #+#             */
/*   Updated: 2025/04/07 17:11:42 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_pipe_precedent(int pipe_precedent)
{
	if (pipe_precedent != -1)
		close(pipe_precedent);
}

void check_fork(pid_t pid, int pipe_precedent, t_cmd *cur_cmd, int fd[2])
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
		return;
	}
}

void exec_simple_cmd(t_cmd *cur_cmd, t_env *env)
{
	int save_stdin;
	int save_stdout;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (cur_cmd->redirection && cur_cmd->cmd != NULL)
	{
		exec_redir(cur_cmd);
	}
	cmd_exec(cur_cmd, env);
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdin);
	close(save_stdout);
}

int has_stdout_redirection(t_cmd *cmd)
{
	t_redirection *redir = cmd->redirection;

	while (redir)
	{
		if (redir->type && (ft_strcmp(redir->type, ">") == 0 || ft_strcmp(redir->type, ">>") == 0))
			return (1);
		redir = redir->next;
	}
	return (0);
}

void child_process(t_cmd *cur_cmd, int fd[2], int pipe_precedent,
				   char **envp, t_env *env)
{
	config_signals_exec();
	if (pipe_precedent != -1)
	{
		dup2(pipe_precedent, STDIN_FILENO);
		close(pipe_precedent);
	}
	if (cur_cmd->next_cmd && !has_stdout_redirection(cur_cmd))
		dup2(fd[1], STDOUT_FILENO);

	close(fd[1]);
	close(fd[0]);

	if (cur_cmd->redirection)
		exec_redir(cur_cmd);

	if (is_cmd(cur_cmd->cmd))
	{
		cmd_exec(cur_cmd, env);
		exit(0);
	}
	exec_process(cur_cmd, fd, env, envp);
	exit(127);
}

int parent_process(int *fd, int pipe_precedent, t_cmd *cur_cmd)
{
	close_pipe_precedent(pipe_precedent);
	if (cur_cmd->next_cmd)
	{
		close(fd[1]);
		return (fd[0]);
	}
	return (-1);
}

void restore_heredoc_stdin(t_cmd *cmd)
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



