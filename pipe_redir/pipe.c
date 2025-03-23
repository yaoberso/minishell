/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:34:51 by nas               #+#    #+#             */
/*   Updated: 2025/03/23 12:06:21 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*found_path(t_cmd *cmd)
{
	char *path;
	char **paths;
	char *full_path;
	char *tmp;
	int i;
	
	path = getenv("PATH"); // recupere l environnement PATH
	if (path == NULL || cmd->cmd == NULL)
		return (NULL);
	paths = ft_split(path, ':'); // separe en liste separe
	if (cmd->cmd[0] == '/' || cmd->cmd[0] == '.')
	{
		if (access(cmd->cmd, F_OK | X_OK) == 0)
		{
			return (ft_strdup(cmd->cmd));
		}
		return (NULL);
		
	}
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/"); // ajoute un / entre le nom du dossier et la commande
		full_path = ft_strjoin(tmp, cmd->cmd);
		free(tmp);
		if (!full_path)
        {
            free_tab(paths);
            return (NULL);
        }
		if (access(full_path, F_OK | X_OK) == 0) // verifie si le fichier existe et si il est executable
			return (free_tab(paths), full_path);
		free(full_path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}


void exec_process(t_cmd *cur_cmd, int fd[2], t_env *env, char **envp)
{
	char **args;
	char *cmd_path;

	if (cur_cmd->cmd == NULL || cur_cmd == NULL)
		return ;
	cmd_path = found_path(cur_cmd);
	if (cur_cmd->redirection && cur_cmd->cmd != NULL && cur_cmd->redirection != NULL) // ici j execute deux fois la redirection
		exec_redir(cur_cmd);
	if (is_cmd(cur_cmd->cmd) == 1)
	{
		cmd_exec(cur_cmd, env);
		free(cmd_path);
		return ;
	}
	args = get_args(cur_cmd); // convertie la liste chainé en tavleau d'arguments pour execve
	if (args == NULL)
	{
		perror("get_args");
		free(cmd_path);
		exit(1);
	}
	if (fd[1] != -1)
		close(fd[1]);
	if (fd[0] != -1)
		close(fd[0]);
	execve(cmd_path, args, envp); // execute la commande en la cherchant dans le path
	perror("execve");
	free(cmd_path); // test de free ici a voir si ca amrche 
	free_tab(args);
	exit(127);
}


void	exec_pipe(t_cmd *cmd, t_env *env, char **envp)
{
	int fd[2];
	pid_t pid;
	t_cmd	*cur_cmd;
	int pipe_precedent;
	int status;
	char *cmd_path;
	int save_stdin;
	int save_stdout;
	

	cur_cmd = cmd;
	pipe_precedent = -1;
	while (cur_cmd)
	{
		if (cur_cmd->next_cmd)
		{
			if (pipe(fd) == -1) // pour cree un pipe
			{
				perror("pipe");
				if (pipe_precedent != -1)
				{
					close(pipe_precedent);
				}
				return ;
			}
		}
		else
		{
			fd[1] = -1;
			fd[0] = -1;
		}
		cmd_path = found_path(cur_cmd);
		if (cmd_path == NULL && is_cmd(cur_cmd->cmd) == 0 && cur_cmd->cmd != NULL)
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
			return ;	
		}
		if (is_cmd(cur_cmd->cmd) == 1 && pipe_precedent == -1 && cur_cmd->next_cmd == NULL)	
		{
			save_stdin = dup(STDIN_FILENO);
			save_stdout = dup(STDOUT_FILENO);
    		if (cur_cmd->redirection && cur_cmd->cmd != NULL && cur_cmd->redirection != NULL)
			{
				exec_redir(cur_cmd);
			}
			cmd_exec(cur_cmd, env);
			dup2(save_stdin, STDIN_FILENO);
			dup2(save_stdout, STDOUT_FILENO);
			close(save_stdin);
			close(save_stdout);
    		return;
		}
		if (cmd_in_pipe(cur_cmd->cmd) == 1 && (cur_cmd->next_cmd != NULL || pipe_precedent != -1)) // si c'est certaines commande interne avec des pipes
		{
			cur_cmd = cur_cmd->next_cmd;
			continue;
		}
		pid = fork();  // cree un processus
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
		// tester echo ls
		
		if (pid == 0) // le processus enfant ou vont s executer les commandes
		{
			// if (cur_cmd->redirection) // ici j execute une fois // tester de supprimer ici et garder l autre !!!!!!!!!!
			// 	exec_redir(cur_cmd);
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
			exec_process(cur_cmd, fd, env, envp);
			exit (1);	
		}
		if (pipe_precedent != -1)
		{
			close(pipe_precedent);
		}
		if (cur_cmd->next_cmd)
		{
			close(fd[1]);
			pipe_precedent = fd[0]; // stock le resultat de fd[0] pour pouvoir le reutiliser au prochain pipe
		}
		cur_cmd = cur_cmd->next_cmd;
	}
	if (pipe_precedent != -1)
	{
		close(pipe_precedent);
	}
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

