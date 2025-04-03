/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:34:51 by nas               #+#    #+#             */
/*   Updated: 2025/04/02 13:45:21 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe(t_cmd *cmd, t_env *env, char **envp)
{
	int		fd[2];
	pid_t	pid;
	t_cmd	*cur_cmd;
	int		pipe_precedent;
	int		status;
	char	*cmd_path;

	status = -1;
	cur_cmd = cmd;
	pipe_precedent = -1;
	while (cur_cmd)
	{
		create_pipe_in_exec(cur_cmd, fd, pipe_precedent);
		cmd_path = found_path(cur_cmd, env);
		if (command_not_found(cur_cmd, pipe_precedent, fd, env) == 1)
			return ;
		if (is_cmd(cur_cmd->cmd) == 1 && pipe_precedent == -1
			&& cur_cmd->next_cmd == NULL)
		{
			exec_simple_cmd(cur_cmd, env);
			free(cmd_path);
			return ;
		}
		if (cmd_in_pipe(cur_cmd->cmd) == 1 && (cur_cmd->next_cmd != NULL
				|| pipe_precedent != -1))
		/* si c'est certaines commande interne avec des pipes*/
		{
			cur_cmd = cur_cmd->next_cmd;
			continue ;
		}
		pid = fork();
		check_fork(pid, pipe_precedent, cur_cmd, fd);
		if (pid == 0)
			child_process(cur_cmd, fd, pipe_precedent, envp);
		pipe_precedent = parent_process(fd, pipe_precedent, cur_cmd);
		cur_cmd = cur_cmd->next_cmd;
	}
	close_pipe_precedent(pipe_precedent);
	exit_status_process(status);
}

// void	exec_pipe(t_cmd *cmd, t_env *env, char **envp)
// {
// 	int		fd[2];
// 	pid_t	pid;
// 	t_cmd	*cur;
// 	int		pipe_precedent;
// 	char	*path;

// 	pipe_precedent = -1;
// 	cur = cmd;
// 	while (cur)
// 	{
// 		create_pipe_in_exec(cur, fd, pipe_precedent);
// 		path = found_path(cur);
// 		if (command_not_found(cur, pipe_precedent, fd) == 1)
// 			return ;
// 		if (is_cmd(cur->cmd) && pipe_precedent == -1 && !cur->next_cmd)
// 			return (exec_simple_cmd(cur, env), free(path));
// 		if (cmd_in_pipe(cur->cmd) && (cur->next_cmd || pipe_precedent != -1))
// 		{
// 			cur = cur->next_cmd;
// 			continue ;
// 		}
// 		else if ((pid = fork()) == 0)
// 			child_process(cur, fd, pipe_precedent, envp);
// 		pipe_precedent = parent_process(fd, pipe_precedent, cur);
// 		cur = cur->next_cmd;
// 	}
// 	close_pipe_precedent(pipe_precedent);
// 	exit_status_process(-1);
// }
