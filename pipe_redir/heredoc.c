/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:43:49 by nas               #+#    #+#             */
/*   Updated: 2025/04/03 12:20:05 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void read_heredoc(t_cmd *cmd, int fd)
{
    char *line;
    
    while (1)
    {
        line = readline("> ");
        // Si readline renvoie NULL ou si SIGINT a été reçu
        if (!line || val_ret == 130)
        {
            if (line)
                free(line);
            return; // Sortir proprement
        }
        
        if (ft_strcmp(line, cmd->redirection->heredoc_delim) == 0) 
        {
            free(line);
            return; // Délimiteur trouvé, sortir proprement
        }
        
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
}

void heredoc_child(t_cmd *cmd, int heredoc_fd[2])
{
    close(heredoc_fd[0]); 
    config_signals_heredoc();
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
    
    close(heredoc_fd[1]);  // Fermer le côté écriture dans le parent
    
    // Attendre l'enfant avec gestion d'interruption
    if (waitpid(pid, &status, 0) == -1)
    {
        if (errno == EINTR)
        {
            // Si waitpid est interrompu par un signal
            val_ret = 130;
            close(heredoc_fd[0]);
            return (1);
        }
        perror("waitpid");
        close(heredoc_fd[0]);
        return (1);
    }
    
    // Vérifier si l'enfant a été interrompu par un signal
    if (WIFSIGNALED(status))
    {
        val_ret = 128 + WTERMSIG(status);
        close(heredoc_fd[0]);
        return (1);
    }
    
    // Vérifier le code de sortie
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
    {
        val_ret = WEXITSTATUS(status);
        close(heredoc_fd[0]);
        return (1);
    }
    
    // Si tout s'est bien passé, rediriger l'entrée
    if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(heredoc_fd[0]);
        return (1);
    }
    
    close(heredoc_fd[0]);
    return (0);
}

// Modifier la fonction redir_heredoc pour utiliser heredoc_child
int redir_heredoc(t_cmd *cmd)
{
    pid_t pid;
    int heredoc_fd[2];
    int status;

    if (pipe(heredoc_fd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    
    // Configurer signaux AVANT le fork
    signal(SIGINT, SIG_IGN); // Ignorer SIGINT dans le processus parent temporairement
    
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        close(heredoc_fd[0]);
        close(heredoc_fd[1]);
        return (-1);
    }
    
    if (pid == 0)
    {
        // Processus enfant
        close(heredoc_fd[0]);
        // Rétablir le gestionnaire SIGINT pour l'enfant
        config_signals_heredoc();
        read_heredoc(cmd, heredoc_fd[1]);
        close(heredoc_fd[1]);
        exit(val_ret); // Utiliser val_ret comme code de sortie
    }
    else
    {
        // Processus parent
        close(heredoc_fd[1]);
        
        // Attendre la fin du processus enfant - avec gestion d'erreur plus robuste
        if (waitpid(pid, &status, 0) == -1)
        {
            if (errno == EINTR) // Spécifiquement pour le cas où waitpid est interrompu
            {
                close(heredoc_fd[0]);
                val_ret = 130;
                return (-1);
            }
            perror("waitpid");
            close(heredoc_fd[0]);
            return (-1);
        }
        
        // Vérifier si l'enfant a été interrompu par un signal
        if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) == 130))
        {
            close(heredoc_fd[0]);
            val_ret = 130;
            return (-1);
        }
        
        // Si le heredoc s'est terminé normalement, rediriger l'entrée
        if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
        {
            perror("dup2");
            close(heredoc_fd[0]);
            return (-1);
        }
        close(heredoc_fd[0]);
    }
    
    // Restaurer les signaux après le heredoc
    config_signals();
    return (0);
}

