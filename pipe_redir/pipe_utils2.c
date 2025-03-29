/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:22:13 by nadahman          #+#    #+#             */
/*   Updated: 2025/03/29 11:14:58 by nas              ###   ########.fr       */
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
		free(cmd_path);
		return (1);	
	}
	return (0);
}



void exit_status_process(int status)
{
	while (wait(&status) > 0)  // attend que tout les process se termine, retourne -1 quand les process finissent
	{
		if (WIFEXITED(status)) // si les process se sont terminé normalement
			val_ret = (WEXITSTATUS(status)); 
		else if (WIFSIGNALED(status)) // si ils se sont stoppé a cause d un signal
		{
			val_ret = 128 + WTERMSIG(status); // id du selon le signal
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








