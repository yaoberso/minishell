/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:34:51 by nas               #+#    #+#             */
/*   Updated: 2025/04/14 13:35:51 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_original_stdin_if_needed(t_cmd *cmd, int *stdin_restored)
{
    if (!*stdin_restored && cmd->std->original_stdin >= 0)
    {
        dup2(cmd->std->original_stdin, STDIN_FILENO);
        close(cmd->std->original_stdin);
        cmd->std->original_stdin = -1;
        *stdin_restored = 1;
    }
}

void exec_pipe(t_cmd *cmd, t_env *env, char **envp)
{
    int fd[2];
    pid_t pid;
    t_cmd *cur_cmd;
    int pipe_precedent;
    int status;
    char *cmd_path;
    int stdin_restored = 0;
    int heredoc_present = 0;

    cmd->std->original_stdin = dup(STDIN_FILENO);
    if (cmd->std->original_stdin == -1)
    {
        perror("dup");
        return;
    }
    cur_cmd = cmd;
    while (cur_cmd)
    {
        if (cur_cmd->redirection)
        {
            if (exec_heredocs(cur_cmd) == 0)
                heredoc_present = 1;
            if (val_ret == 130)
            {
                if (cur_cmd->save_stdin >= 0)
                    close(cur_cmd->save_stdin);
                close_original_stdin_if_needed(cmd, &stdin_restored);
                return;
            }
        }
        cur_cmd = cur_cmd->next_cmd;
    }
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
            close_pipes(fd);
            close_original_stdin_if_needed(cmd, &stdin_restored);
            restore_signals();
            return;
        }

        if (is_cmd(cur_cmd->cmd) == 1 && pipe_precedent == -1 && cur_cmd->next_cmd == NULL)
        {
            exec_simple_cmd(cur_cmd, env);
            if (cmd_path)
                free(cmd_path);
            close_pipes(fd);
            close_original_stdin_if_needed(cmd, &stdin_restored);
            restore_signals();
            return;
        }

 
        if (cmd_in_pipe(cur_cmd->cmd) == 1 && (cur_cmd->next_cmd != NULL || pipe_precedent != -1))
        {
            if (cmd_path)
                free(cmd_path);
            close_pipes(fd);
            close_original_stdin_if_needed(cmd, &stdin_restored);
            if (cur_cmd->save_stdin != -1)
                close(cur_cmd->save_stdin);
            cur_cmd = cur_cmd->next_cmd;
            continue;
        }

        pid = fork();
        check_fork(pid, pipe_precedent, cur_cmd, fd);

        if (pid == 0)
        {
            if (cmd->std->original_stdin >= 0)
                close(cmd->std->original_stdin);
            if (cmd_path)
                free(cmd_path);
            child_process(cur_cmd, fd, pipe_precedent, envp, env);
        }

        if (cmd_path)
            free(cmd_path);
        pipe_precedent = parent_process(fd, pipe_precedent, cur_cmd);
        cur_cmd = cur_cmd->next_cmd;
    }

    close_pipe_precedent(pipe_precedent);
    exit_status_process(status);
    close_pipes(fd);
    close_original_stdin_if_needed(cmd, &stdin_restored);

    if (heredoc_present)
    {
        cur_cmd = cmd;
        while (cur_cmd)
        {
            if (cur_cmd->save_stdin != -1)
                close(cur_cmd->save_stdin);
            cur_cmd = cur_cmd->next_cmd;
        }
    }
    restore_signals();
}

// void close_original_stdin_if_needed(t_cmd *cmd, int *stdin_restored)
// {
// 	if (!*stdin_restored && cmd->std->original_stdin >= 0)
// 	{
// 		dup2(cmd->std->original_stdin, STDIN_FILENO);
// 		close(cmd->std->original_stdin);
// 		cmd->std->original_stdin = -1;
// 		*stdin_restored = 1;
// 	}
// }

// void exec_pipe(t_cmd *cmd, t_env *env, char **envp)
// {
//     int     fd[2];
//     pid_t   pid;
//     t_cmd   *cur_cmd;
//     int     pipe_precedent;
//     int     status;
//     char    *cmd_path;
//     int     stdin_restored = 0;
//     int     heredoc_present = 0;

//     cmd->std->original_stdin = dup(STDIN_FILENO);
//     if (cmd->std->original_stdin == -1)
//     {
//         perror("dup");
//         return;
//     }
//     cur_cmd = cmd;
//     while (cur_cmd)
//     {
//         if (cur_cmd->redirection)
//         {
//             if (exec_heredocs(cur_cmd) == 0)
//                 heredoc_present = 1;
//             if (val_ret == 130)
//             {
//                 if (cur_cmd->save_stdin >= 0)
//                 {
// 	                close(cur_cmd->save_stdin);
// 	                cur_cmd->save_stdin = -1;
//                 }
//                 close_original_stdin_if_needed(cmd, &stdin_restored);

//                 return;
//             }
//         }
//         cur_cmd = cur_cmd->next_cmd;
//     }
//     config_signals_exec();

//     status = -1;
//     cur_cmd = cmd;
//     pipe_precedent = -1;

//     while (cur_cmd)
//     {
//         create_pipe_in_exec(cur_cmd, fd, pipe_precedent);
//         cmd_path = found_path(cur_cmd, env);

//         if (command_not_found(cur_cmd, pipe_precedent, fd, env) == 1)
//         {
//             if (cmd_path)
//                 free(cmd_path);
//             close_pipes(fd);
//             if (!stdin_restored)
//             close_original_stdin_if_needed(cmd, &stdin_restored);

//             restore_signals();
//             return;
//         }

//         if (is_cmd(cur_cmd->cmd) == 1 && pipe_precedent == -1 && cur_cmd->next_cmd == NULL)
//         {
//             exec_simple_cmd(cur_cmd, env);
//             if (cmd_path)
//                 free(cmd_path);
//             close_pipes(fd);
//             close_original_stdin_if_needed(cmd, &stdin_restored);

//             restore_signals();
//             return;
//         }

//         if (cmd_in_pipe(cur_cmd->cmd) == 1 && (cur_cmd->next_cmd != NULL || pipe_precedent != -1))
//         {
//             if (cmd_path)
//                 free(cmd_path);
//             close_pipes(fd);
//             close_original_stdin_if_needed(cmd, &stdin_restored);
//             if (cur_cmd->save_stdin != -1)
//             {
// 	            close(cur_cmd->save_stdin);
// 	            cur_cmd->save_stdin = -1;
//             }

//             cur_cmd = cur_cmd->next_cmd;
//             continue;
//         }

//         pid = fork();
//         check_fork(pid, pipe_precedent, cur_cmd, fd);

//         if (pid == 0)
//         {
//             if (cmd->std->original_stdin >= 0)
//                 close(cmd->std->original_stdin);
//             if (cmd_path)
//                 free(cmd_path);
//             child_process(cur_cmd, fd, pipe_precedent, envp, env);
//         }

//         // Dans le parent
//         if (cmd_path)
//             free(cmd_path);
//         pipe_precedent = parent_process(fd, pipe_precedent, cur_cmd);
//         cur_cmd = cur_cmd->next_cmd;
//     }

//     close_pipe_precedent(pipe_precedent);
//     exit_status_process(status);
//     // Restaurer le stdin original
//     close_pipes(fd);
//     close_original_stdin_if_needed(cmd, &stdin_restored);

//     if (heredoc_present)
//     {
//         cur_cmd = cmd;
//         while (cur_cmd)
//         {
//             if (cur_cmd->save_stdin != -1)
//             {
//                 close(cur_cmd->save_stdin);
//                 cur_cmd->save_stdin = -1;
//             }
//             cur_cmd = cur_cmd->next_cmd;
//         }
//     }
//     restore_signals();
// }
