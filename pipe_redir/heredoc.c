/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:13:35 by nas               #+#    #+#             */
/*   Updated: 2025/04/17 13:29:02 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_heredoc(t_cmd *cmd, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(STDOUT_FILENO, "\n", 1);
			break ;
		}
		if (ft_strcmp(line, cmd->redirection->heredoc_delim) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	heredoc_child(t_cmd *cmd, int heredoc_fd[2])
{
	close(heredoc_fd[0]);
	config_signals_heredoc();
	read_heredoc(cmd, heredoc_fd[1]);
	dup2(cmd->std->original_stdin, STDIN_FILENO);
	close(cmd->std->original_stdin);
	free_env(cmd->env);
	free_cmd(cmd);
	close(heredoc_fd[1]);
	exit(0);
}

int	heredoc_pipe(int heredoc_fd[2])
{
	if (pipe(heredoc_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

int	redir_heredoc(t_cmd *cmd)
{
	pid_t	pid;
	int		heredoc_fd[2];
	int		status;

	if (setup_heredoc(cmd, heredoc_fd) != 0)
		return (-1);
	pid = heredoc_fork(cmd, heredoc_fd);
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		if (cmd->save_stdin >= 0)
			close(cmd->save_stdin);
		heredoc_child(cmd, heredoc_fd);
	}
	else
	{
		status = heredoc_parent(pid, heredoc_fd);
		return (heredoc_cleanup(cmd, heredoc_fd[0], status));
	}
	return (0);
}
