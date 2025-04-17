/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:36:37 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/15 12:36:01 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_parent(pid_t pid, int heredoc_fd[2])
{
	int	status;

	close(heredoc_fd[1]);
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		close(heredoc_fd[0]);
		return (1);
	}
	if (WIFSIGNALED(status) || (WIFEXITED(status)
			&& WEXITSTATUS(status) == 130))
	{
		close(heredoc_fd[0]);
		return (1);
	}
	if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(heredoc_fd[0]);
		return (1);
	}
	close(heredoc_fd[0]);
	return (0);
}

int	setup_heredoc(t_cmd *cmd, int heredoc_fd[2])
{
	cmd->save_stdin = dup(STDIN_FILENO);
	if (cmd->save_stdin == -1)
	{
		perror("dup");
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	if (heredoc_pipe(heredoc_fd) != 0)
	{
		close(cmd->save_stdin);
		cmd->save_stdin = -1;
		return (-1);
	}
	return (0);
}

int	heredoc_fork(t_cmd *cmd, int heredoc_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(heredoc_fd[0]);
		close(heredoc_fd[1]);
		close(cmd->save_stdin);
		cmd->save_stdin = -1;
		restore_signals();
		return (-1);
	}
	return (pid);
}

int	heredoc_cleanup(t_cmd *cmd, int fd, int status)
{
	if (status != 0)
	{
		close(fd);
		dup2(cmd->save_stdin, STDIN_FILENO);
		close(cmd->save_stdin);
		cmd->save_stdin = -1;
		restore_signals();
		return (-1);
	}
	close(cmd->save_stdin);
	close(fd);
	restore_signals();
	return (0);
}
