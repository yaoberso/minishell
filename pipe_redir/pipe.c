/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:34:51 by nas               #+#    #+#             */
/*   Updated: 2025/04/08 10:54:55 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_pipe(t_cmd *cmd, t_env *env, char **envp)
{
    int     fd[2];
    pid_t   pid;
    t_cmd   *cur_cmd;
    int     pipe_precedent;
    int     status;
    char    *cmd_path;
    int     original_stdin;
    int     heredoc_present = 0;

    // Sauvegarder le stdin original pour tout le traitement
    original_stdin = dup(STDIN_FILENO);
    if (original_stdin == -1)
    {
        perror("dup");
        return;
    }

    // Traitement des heredocs d'abord
    cur_cmd = cmd;
    while (cur_cmd)
    {
        if (cur_cmd->redirection)
        {   
            if (exec_heredocs(cur_cmd) == 0)
                heredoc_present = 1;
            
            // Si un signal a interrompu (comme CTRL+C)
            if (val_ret == 130)
            {
                dup2(original_stdin, STDIN_FILENO);
                close(original_stdin);
                return;
            }
        }
        cur_cmd = cur_cmd->next_cmd;
    }

    // Configuration des signaux pour l'exécution des commandes
    config_signals_exec();
    
    status = -1;
    cur_cmd = cmd;
    pipe_precedent = -1;
    
    while (cur_cmd)
    {
        create_pipe_in_exec(cur_cmd, fd, pipe_precedent);
        cmd_path = found_path(cur_cmd, env);
        
        if (command_not_found(cur_cmd, pipe_precedent, fd, env) == 1)
        {
            if (cmd_path)
                free(cmd_path);
            dup2(original_stdin, STDIN_FILENO);
            close(original_stdin);
            restore_signals();
            return;
        }
        
        if (is_cmd(cur_cmd->cmd) == 1 && pipe_precedent == -1 && cur_cmd->next_cmd == NULL)
        {
            exec_simple_cmd(cur_cmd, env);
            if (cmd_path)
                free(cmd_path);
            dup2(original_stdin, STDIN_FILENO);
            close(original_stdin);
            restore_signals();
            return;
        }
        
        if (cmd_in_pipe(cur_cmd->cmd) == 1 && (cur_cmd->next_cmd != NULL || pipe_precedent != -1))
        {
            if (cmd_path)
                free(cmd_path);
            cur_cmd = cur_cmd->next_cmd;
            continue;
        }
        
        pid = fork();
        check_fork(pid, pipe_precedent, cur_cmd, fd);
        
        if (pid == 0)
        {
            close(original_stdin);
            if (cmd_path)
                free(cmd_path);
            child_process(cur_cmd, fd, pipe_precedent, envp, env);
        }
        
        // Dans le parent
        if (cmd_path)
            free(cmd_path);
        pipe_precedent = parent_process(fd, pipe_precedent, cur_cmd);
        cur_cmd = cur_cmd->next_cmd;
    }
    
    close_pipe_precedent(pipe_precedent);
    exit_status_process(status);
    
    // Restaurer le stdin original
    dup2(original_stdin, STDIN_FILENO);
    close(original_stdin);
    
    if (heredoc_present)
    {
        cur_cmd = cmd;
        while (cur_cmd)
        {
            if (cur_cmd->save_stdin != -1)
            {
                close(cur_cmd->save_stdin);
                cur_cmd->save_stdin = -1;
            }
            cur_cmd = cur_cmd->next_cmd;
        }
    }
    restore_signals();
}
