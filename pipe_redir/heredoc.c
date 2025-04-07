/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:13:35 by nas               #+#    #+#             */
/*   Updated: 2025/04/07 12:44:12 by nas              ###   ########.fr       */
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
        return (1);  // Modification: return(1) au lieu de exit(1)
    }

    close(heredoc_fd[0]);
    return (0);
}

int redir_heredoc(t_cmd *cmd)
{
    pid_t pid;
    int heredoc_fd[2];
    int status;
    int saved_stdin;

    // Sauvegarder l'entrée standard
    saved_stdin = dup(STDIN_FILENO);
    if (saved_stdin == -1)
    {
        perror("dup");
        return (-1);
    }

    config_signals_heredoc();
    if (heredoc_pipe(heredoc_fd) != 0)
    {
        close(saved_stdin);
        return (-1);
    }
    
    printf("DEBUG: Avant fork pour heredoc\n");
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        close(heredoc_fd[0]);
        close(heredoc_fd[1]);
        close(saved_stdin);
        return (-1);
    }
    
    if (pid == 0)
    {
        // Processus enfant
        printf("DEBUG: Processus enfant heredoc (PID: %d)\n", getpid());
        close(saved_stdin); // On n'a pas besoin du stdin sauvegardé dans l'enfant
        heredoc_child(cmd, heredoc_fd);
        // Ne devrait jamais arriver ici, mais par sécurité:
        printf("DEBUG: ERREUR - L'enfant heredoc n'a pas quitté correctement\n");
        exit(1);
    }
    else
    {
        // Processus parent
        printf("DEBUG: Processus parent (PID: %d) attend heredoc (PID: %d)\n", getpid(), pid);
        close(heredoc_fd[1]); // Fermer le côté écriture du pipe
        
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            close(heredoc_fd[0]);
            dup2(saved_stdin, STDIN_FILENO);
            close(saved_stdin);
            return (-1);
        }
        
        printf("DEBUG: Enfant heredoc (PID: %d) terminé avec statut: %d\n", pid, status);
        
        // Vérifier si l'enfant s'est terminé normalement
        if (WIFSIGNALED(status))
        {
            printf("DEBUG: Enfant heredoc terminé par signal: %d\n", WTERMSIG(status));
            val_ret = 130; // Signalé
            close(heredoc_fd[0]);
            dup2(saved_stdin, STDIN_FILENO);
            close(saved_stdin);
            return (-1);
        }
        else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            printf("DEBUG: Enfant heredoc a quitté avec code: %d\n", WEXITSTATUS(status));
            val_ret = WEXITSTATUS(status);
            close(heredoc_fd[0]);
            dup2(saved_stdin, STDIN_FILENO);
            close(saved_stdin);
            return (-1);
        }
        
        // Rediriger STDIN vers le pipe
        printf("DEBUG: Redirection de STDIN vers le pipe heredoc\n");
        if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
        {
            perror("dup2");
            close(heredoc_fd[0]);
            dup2(saved_stdin, STDIN_FILENO);
            close(saved_stdin);
            return (-1);
        }
        
        close(heredoc_fd[0]); // Plus besoin après dup2
    }
    
    restore_signals();
    // Nous conservons saved_stdin pour pouvoir restaurer plus tard
    cmd->save_stdin = saved_stdin; // Tu devras ajouter ce champ à la structure t_cmd
    
    printf("DEBUG: Heredoc terminé avec succès\n");
    return (0);
}