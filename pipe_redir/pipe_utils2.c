/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:22:13 by nadahman          #+#    #+#             */
/*   Updated: 2025/03/27 10:34:10 by nadahman         ###   ########.fr       */
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

int	command_not_found(t_cmd *cur_cmd, int pipe_precedent, int fd[2])
{
	char *cmd_path;

	cmd_path = found_path(cur_cmd);
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
		return (1);	
	}
	return (0);
}

// void	create_fork(int pipe_precedent, t_cmd *cur_cmd, int fd[2])
// {
// 	pid_t pid;

// 	pid = fork();  // cree un processus
// 	if (pid < 0)
// 	{
// 		perror("fork");
// 		if (pipe_precedent != -1)
// 			close(pipe_precedent);
// 		if (cur_cmd->next_cmd)
// 		{
// 			close(fd[0]);
// 			close(fd[1]);
// 		}
// 		return ;
// 	}
// }


// 5 3 1
// 8 1
// 9 0
