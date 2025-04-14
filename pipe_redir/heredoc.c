/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:13:35 by nas               #+#    #+#             */
/*   Updated: 2025/04/14 10:02:27 by yann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void read_heredoc(t_cmd *cmd, int fd)
{
    char *line;

    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
        // if (val_ret == 130)
        // {
        //     free(line);
        //     break;
        // }
        if (ft_strcmp(line, cmd->redirection->heredoc_delim) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line)); // ecrit la ligne dans le fd
        write(fd, "\n", 1);
        free(line);
    }
}

void heredoc_child(t_cmd *cmd, int heredoc_fd[2])
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

int heredoc_pipe(int heredoc_fd[2])
{
    if (pipe(heredoc_fd) == -1)
    {
        perror("pipe");
        return (1);
    }
    return (0);
}

int heredoc_parent(pid_t pid, int heredoc_fd[2])
{
    int status;

    close(heredoc_fd[1]);
    if (waitpid(pid, &status, 0) == -1)
    {
        perror("waitpid");
        close(heredoc_fd[0]);
        return (1);
    }
    if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) == 130))
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

int redir_heredoc(t_cmd *cmd)
{
	pid_t pid;
	int heredoc_fd[2];
	int ret;
	
	if (init_heredoc(cmd, heredoc_fd) != 0)
		return (-1);
	
	pid = fork_heredoc(cmd, heredoc_fd);
	if (pid == -1)
		return (-1);
	else if (pid > 0)
	{
		close(heredoc_fd[1]);
		ret = check_heredoc_status(cmd, heredoc_fd, pid);
		if (ret != 0)
			return (ret);
		return (finalize_heredoc(cmd, heredoc_fd));
	}
	
	return (0);
}
int redir_heredoc(t_cmd *cmd)
{
	pid_t pid;
	int heredoc_fd[2];
	int ret;
	
	if (init_heredoc(cmd, heredoc_fd) != 0)
		return (-1);
	
	pid = fork_heredoc(cmd, heredoc_fd);
	if (pid == -1)
		return (-1);
	else if (pid > 0)
	{
		close(heredoc_fd[1]);
		ret = check_heredoc_status(cmd, heredoc_fd, pid);
		if (ret != 0)
			return (ret);
		return (finalize_heredoc(cmd, heredoc_fd));
	}
	
	return (0);
}
