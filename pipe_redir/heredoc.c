/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:43:49 by nas               #+#    #+#             */
/*   Updated: 2025/03/10 11:23:45 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void read_heredoc(t_cmd *cmd, int fd)
{
    char *line;
    
   if (cmd->redirection->heredoc_delim != NULL)
   {
        while (1)
        {
            line = readline("> "); //pour cree un prompt
            if (!line || ft_strcmp(line, cmd->redirection->heredoc_delim) == 0) 
            {
                free(line);
                break;
            }
            write(fd, line, ft_strlen(line)); // ecrit la ligne dans le fd
            write(fd, "\n", 1); 
            free(line);
        }
   }
}

void heredoc_child(t_cmd *cmd, int heredoc_fd[2])
{
    config_signals();
    close(heredoc_fd[0]);
    read_heredoc(cmd, heredoc_fd[1]);
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
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) == 130)) // si un signal stop tout ou si il s est termine normalement ou par ctrl c
    {
        close(heredoc_fd[0]);
        return (1);
    }
    if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(heredoc_fd[0]);
        exit(1);
    }
    close(heredoc_fd[0]);
    return (0);
}

void redir_heredoc(t_cmd *cmd, int heredoc_fd[2])
{
    pid_t pid;
    
    if (heredoc_pipe(heredoc_fd) != 0)
    {
        close(heredoc_fd[0]);
        close(heredoc_fd[1]);
        exit(1);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        close(heredoc_fd[0]);
        close(heredoc_fd[1]);
        exit(1);
    }
    if (pid == 0)
    {
        heredoc_child(cmd, heredoc_fd);
    }
    else
    {
        if (heredoc_parent(pid, heredoc_fd) != 0)
            return;
    }
}
