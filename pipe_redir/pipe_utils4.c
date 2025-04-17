/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:31:19 by nas               #+#    #+#             */
/*   Updated: 2025/04/15 12:57:09 by yaoberso         ###   ########.fr       */
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
	cur_cmd->std->save_instd = dup(STDIN_FILENO);
	cur_cmd->std->save_outstd = dup(STDOUT_FILENO);
	if (cur_cmd->redirection && cur_cmd->cmd != NULL)
	{
		exec_redir(cur_cmd);
	}
	cmd_exec(cur_cmd, env);
	dup2(cur_cmd->std->save_instd, STDIN_FILENO);
	dup2(cur_cmd->std->save_outstd, STDOUT_FILENO);
	close(cur_cmd->std->save_instd);
	close(cur_cmd->std->save_outstd);
}

int	has_stdout_redirection(t_cmd *cmd)
{
	t_redirection	*redir;

	redir = cmd->redirection;
	while (redir)
	{
		if (redir->type && (ft_strcmp(redir->type, ">") == 0
				|| ft_strcmp(redir->type, ">>") == 0))
			return (1);
		redir = redir->next;
	}
	return (0);
}

void	child_process(t_cmd *cur_cmd, int fd[2], int pipe_precedent,
		char **envp)
{
	config_signals_exec();
	if (pipe_precedent != -1)
	{
		dup2(pipe_precedent, STDIN_FILENO);
		close(pipe_precedent);
	}
	if (cur_cmd->next_cmd && !has_stdout_redirection(cur_cmd))
		dup2(fd[1], STDOUT_FILENO);
	close_pipes(fd);
	if (cur_cmd->redirection)
		exec_redir(cur_cmd);
	if (is_cmd(cur_cmd->cmd))
	{
		cmd_exec(cur_cmd, cur_cmd->env);
		free_env(cur_cmd->env);
		free_cmd(cur_cmd);
		exit(0);
	}
	exec_process(cur_cmd, fd, cur_cmd->env, envp);
	free_env(cur_cmd->env);
	free_cmd(cur_cmd);
	exit(127);
}
