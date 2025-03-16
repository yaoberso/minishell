/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:34:51 by nas               #+#    #+#             */
/*   Updated: 2025/03/16 20:36:37 by nas              ###   ########.fr       */
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
	
	path = getenv("PATH");
	if (path == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd->cmd);
		free(tmp);
		if (!full_path)
        {
            free_tab(paths);
            return (NULL);
        }
		if (access(full_path, F_OK | X_OK) == 0) 
			return (free_tab(paths), full_path);
		free(full_path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

void exec_process(t_cmd *cur_cmd, int fd[2])
{
	char **args;
	char *cmd_path;

	cmd_path = found_path(cur_cmd);
	if (cur_cmd->redirection) // si il y a une redirection il l'execute
		exec_redir(cur_cmd);
	args = get_args(cur_cmd); // convertie la liste chainé en tavleau d'arguments pour execve
	if (args == NULL)
	{
		perror("get_args");
		exit(1);
	}
	if (fd[1] != -1)
		close(fd[1]);
	if (fd[0] != -1)
		close(fd[0]);
	execve(found_path(cur_cmd), args, NULL); // execute la commande en la cherchant dans le path
	perror("execve");
	free(cmd_path); // test de free ici a voir si ca amrche 
	free_tab(args);
	exit(127);
}


void	exec_pipe(t_cmd *cmd, t_env *env)
{
	int fd[2];
	pid_t pid;
	t_cmd	*cur_cmd;
	int pipe_precedent;
	int status;
	char *cmd_path;
	int	save_stdin;
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
		if (cmd_path == NULL && is_cmd(cur_cmd->cmd) == 0)
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
		if (is_cmd(cur_cmd->cmd) == 1 && pipe_precedent == -1 && cur_cmd->next_cmd == NULL)  // si cest une commande interne seul
		{
			if (cur_cmd->redirection)     // la il faut faire fonctionner la redirection
			{
				save_stdout = dup(STDOUT_FILENO); // sauvegarde les descripteurs avant de les rediriger sinon le prompt s ecris dans le fichier
        		save_stdin = dup(STDIN_FILENO);
				exec_redir(cur_cmd);
				cmd_exec(cur_cmd, env);
				dup2(save_stdin, STDIN_FILENO); // on remet les descripteurs de base pour que le prompt s affiche correctement
				dup2(save_stdout, STDOUT_FILENO);
				close(save_stdin);
				close(save_stdout);
				if (cur_cmd->save_stdin > 0) // si on a utilisé un heredoc on ferme le fd sauvegardé
				{
					close(cur_cmd->save_stdin);
					cur_cmd->save_stdin = -1; // et on reinitialise
				}
			}
			else
				cmd_exec(cur_cmd, env);
			return ;
		}
		if (cmd_in_pipe(cur_cmd->cmd) == 1 && (cur_cmd->next_cmd != NULL || pipe_precedent != -1)) // si c'est certaines commande interne avec des pipes
		{
			printf("ici je dois gerer l erreur pour ce cas\n");
			return ;
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
			if (cur_cmd->redirection)
				exec_redir(cur_cmd);
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
			exec_process(cur_cmd, fd);
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

