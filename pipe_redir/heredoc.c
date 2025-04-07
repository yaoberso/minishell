/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:13:35 by nas               #+#    #+#             */
/*   Updated: 2025/04/07 16:57:40 by nas              ###   ########.fr       */
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
    
    // Sauvegarder l'entrée standard
    cmd->save_stdin = dup(STDIN_FILENO);
    if (cmd->save_stdin == -1)
    {
        perror("dup");
        return (-1);
    }

    // Configurer les signaux pour le heredoc dans le processus parent
    signal(SIGINT, SIG_IGN); // Ignorer SIGINT temporairement dans le parent
    
    if (heredoc_pipe(heredoc_fd) != 0)
    {
        close(cmd->save_stdin);
        cmd->save_stdin = -1;
        return (-1);
    }
    
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        close(heredoc_fd[0]);
        close(heredoc_fd[1]);
        close(cmd->save_stdin);
        cmd->save_stdin = -1;
        restore_signals(); // Restaurer les signaux en cas d'erreur
        return (-1);
    }
    
    if (pid == 0) // Processus enfant
    {
        // Restaurer le comportement par défaut de SIGINT dans l'enfant
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_IGN);
        close(cmd->save_stdin);
        heredoc_child(cmd, heredoc_fd);
        // Ne devrait jamais atteindre ce point
    }
    else // Processus parent
    {
        close(heredoc_fd[1]); // Fermer le côté écriture du pipe
        
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            close(heredoc_fd[0]);
            dup2(cmd->save_stdin, STDIN_FILENO);
            close(cmd->save_stdin);
            cmd->save_stdin = -1;
            restore_signals();
            return (-1);
        }
        
        // Vérifier si l'enfant a été interrompu par un signal
        if (WIFSIGNALED(status))
        {
            val_ret = 130; // SIGINT
            close(heredoc_fd[0]);
            dup2(cmd->save_stdin, STDIN_FILENO);
            close(cmd->save_stdin);
            cmd->save_stdin = -1;
            restore_signals();
            return (-1);
        }
        
        // Vérifier si l'enfant s'est terminé avec un code de sortie non nul
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            val_ret = WEXITSTATUS(status);
            close(heredoc_fd[0]);
            dup2(cmd->save_stdin, STDIN_FILENO);
            close(cmd->save_stdin);
            cmd->save_stdin = -1;
            restore_signals();
            return (-1);
        }
        
        // Rediriger l'entrée standard vers le pipe
        if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
        {
            perror("dup2");
            close(heredoc_fd[0]);
            dup2(cmd->save_stdin, STDIN_FILENO);
            close(cmd->save_stdin);
            cmd->save_stdin = -1;
            restore_signals();
            return (-1);
        }
        
        close(heredoc_fd[0]);
        restore_signals(); // Restaurer les signaux pour le processus parent
    }
    
    // Le save_stdin reste valide pour être restauré plus tard
    return (0);
}

// int redir_heredoc(t_cmd *cmd)
// {
//     pid_t pid;
//     int heredoc_fd[2];
//     int status;
//     int saved_stdin;

//     // Sauvegarder l'entrée standard
//     saved_stdin = dup(STDIN_FILENO);
//     if (saved_stdin == -1)
//     {
//         perror("dup");
//         return (-1);
//     }

//     config_signals_heredoc();
//     if (heredoc_pipe(heredoc_fd) != 0)
//     {
//         close(saved_stdin);
//         return (-1);
//     }
//     pid = fork();
//     if (pid == -1)
//     {
//         perror("fork");
//         close(heredoc_fd[0]);
//         close(heredoc_fd[1]);
//         close(saved_stdin);
//         return (-1);
//     }
    
//     if (pid == 0)
//     {
//         // Processus enfant
//         close(saved_stdin);
//         heredoc_child(cmd, heredoc_fd);
//         exit(1);
//     }
//     else
//     {
//         close(heredoc_fd[1]); // Fermer le côté écriture du pipe
        
//         if (waitpid(pid, &status, 0) == -1)
//         {
//             perror("waitpid");
//             close(heredoc_fd[0]);
//             dup2(saved_stdin, STDIN_FILENO);
//             close(saved_stdin);
//             return (-1);
//         }
//         if (WIFSIGNALED(status))
//         {
//             val_ret = 130; // Signalé
//             close(heredoc_fd[0]);
//             dup2(saved_stdin, STDIN_FILENO);
//             close(saved_stdin);
//             return (-1);
//         }
//         else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
//         {
//             val_ret = WEXITSTATUS(status);
//             close(heredoc_fd[0]);
//             dup2(saved_stdin, STDIN_FILENO);
//             close(saved_stdin);
//             return (-1);
//         }
//         if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
//         {
//             perror("dup2");
//             close(heredoc_fd[0]);
//             dup2(saved_stdin, STDIN_FILENO);
//             close(saved_stdin);
//             return (-1);
//         }
        
//         close(heredoc_fd[0]);
//     }
    
//     restore_signals();
//     cmd->save_stdin = saved_stdin;
//     return (0);
// }