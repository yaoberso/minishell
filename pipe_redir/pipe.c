/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:34:51 by nas               #+#    #+#             */
/*   Updated: 2025/04/07 13:00:31 by nas              ###   ########.fr       */
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
    pid_t   *child_pids; // Tableau pour suivre tous les PIDs des enfants
    int     child_count = 0;
    int     i;

    // Compter le nombre de commandes pour allouer le tableau de PIDs
    cur_cmd = cmd;
    int cmd_count = 0;
    while (cur_cmd) {
        cmd_count++;
        cur_cmd = cur_cmd->next_cmd;
    }
    
    child_pids = malloc(sizeof(pid_t) * cmd_count);
    if (!child_pids) {
        perror("malloc");
        return;
    }

    // Traitement des heredocs d'abord
    cur_cmd = cmd;
    while (cur_cmd)
    {
        if (cur_cmd->redirection && exec_heredocs(cur_cmd) == -1)
        {
            free(child_pids);
            return;
        }

        if (val_ret == 130) // Ctrl+C ou erreur heredoc
        {
            free(child_pids);
            return;
        }
        cur_cmd = cur_cmd->next_cmd;
    }

    status = -1;
    cur_cmd = cmd;
    pipe_precedent = -1;
    while (cur_cmd)
    {
        create_pipe_in_exec(cur_cmd, fd, pipe_precedent);
        cmd_path = found_path(cur_cmd, env);
        
        if (command_not_found(cur_cmd, pipe_precedent, fd, env) == 1)
        {
            free(child_pids);
            return;
        }
        
        // Cas de commande simple sans pipe
        if (is_cmd(cur_cmd->cmd) == 1 && pipe_precedent == -1 && cur_cmd->next_cmd == NULL)
        {
            exec_simple_cmd(cur_cmd, env);
            free(cmd_path);
            free(child_pids);
            return;
        }
        
        // Cas de commandes internes avec des pipes
        if (cmd_in_pipe(cur_cmd->cmd) == 1 && (cur_cmd->next_cmd != NULL || pipe_precedent != -1))
        {
            free(cmd_path);
            cur_cmd = cur_cmd->next_cmd;
            continue;
        }
        
        pid = fork();
        check_fork(pid, pipe_precedent, cur_cmd, fd);
        
        if (pid == 0)
        {
            // Processus enfant
            free(child_pids); // L'enfant n'a pas besoin de ce tableau
            child_process(cur_cmd, fd, pipe_precedent, envp, env);
            // Ne devrait jamais arriver ici car child_process appelle exit()
            exit(1);
        }
        else
        {
            // Processus parent - enregistrer le PID de l'enfant
            child_pids[child_count++] = pid;
        }
        
        // Processus parent
        free(cmd_path);
        pipe_precedent = parent_process(fd, pipe_precedent, cur_cmd);
        cur_cmd = cur_cmd->next_cmd;
    }
    
    // Fermer le dernier pipe si nécessaire
    close_pipe_precedent(pipe_precedent);
    
    // Attendre tous les enfants
   exit_status_process(status);
    free(child_pids);
    
    // Nettoyer les ressources des heredocs
    cur_cmd = cmd;
    while (cur_cmd)
    {
        if (cur_cmd->save_stdin != -1)
        {
            restore_heredoc_stdin(cur_cmd);
        }
        cur_cmd = cur_cmd->next_cmd;
    }
}

// void	exec_pipe(t_cmd *cmd, t_env *env, char **envp)
// {
// 	int		fd[2];
// 	pid_t	pid;
// 	t_cmd	*cur_cmd;
// 	int		pipe_precedent;
// 	int		status;
// 	char	*cmd_path;

// 	cur_cmd = cmd;
// 	while (cur_cmd)
// 	{
// 		if (cur_cmd->redirection)
// 			exec_heredocs(cur_cmd);
// 		cur_cmd = cur_cmd->next_cmd;
// 	}
// 	status = -1;
// 	cur_cmd = cmd;
// 	pipe_precedent = -1;
// 	while (cur_cmd)
// 	{
// 		create_pipe_in_exec(cur_cmd, fd, pipe_precedent);
// 		cmd_path = found_path(cur_cmd, env);
// 		if (command_not_found(cur_cmd, pipe_precedent, fd, env) == 1)
// 			return ;
// 		if (is_cmd(cur_cmd->cmd) == 1 && pipe_precedent == -1
// 			&& cur_cmd->next_cmd == NULL)
// 		{
// 			exec_simple_cmd(cur_cmd, env);
// 			free(cmd_path);
// 			return ;
// 		}
// 		if (cmd_in_pipe(cur_cmd->cmd) == 1 && (cur_cmd->next_cmd != NULL
// 				|| pipe_precedent != -1))
// 		/* si c'est certaines commande interne avec des pipes*/
// 		{
// 			cur_cmd = cur_cmd->next_cmd;
// 			continue ;
// 		}
// 		pid = fork();
// 		check_fork(pid, pipe_precedent, cur_cmd, fd);
// 		if (pid == 0)
// 			child_process(cur_cmd, fd, pipe_precedent, envp, env);
// 		pipe_precedent = parent_process(fd, pipe_precedent, cur_cmd);
// 		cur_cmd = cur_cmd->next_cmd;
// 	}
// 	close_pipe_precedent(pipe_precedent);
// 	exit_status_process(status);
// }

