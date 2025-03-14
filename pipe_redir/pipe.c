/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:34:51 by nas               #+#    #+#             */
/*   Updated: 2025/03/14 12:49:33 by nas              ###   ########.fr       */
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
		if (access(full_path, F_OK | X_OK) == 0) 
			return (free_tab(paths), full_path);
		free(full_path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

void exec_process(t_cmd *cur_cmd, t_cmd *next_cmd, int fd[2], t_env *env)
{
	char **args;

	if (is_cmd(cur_cmd->cmd) == 1 && cur_cmd->prev_cmd)
	{
   		printf("%s: fonctionne pas dans un pipe\n", cur_cmd->cmd);    // a voir si je garde selon le comprortement de bash
		val_ret = 1;
    	exit(1);
	}

	if (cur_cmd->prev_cmd) // si il y a une commande avant il redirige l'entree vers stdin
		redir_stdin(fd);
	if (next_cmd) // si il y a une commande apres il redirige la sortie vers stdout
		redir_stdout(fd, next_cmd);
	if (cur_cmd->redirection) // si il y a une redirection il l'execute
		exec_redir(cur_cmd);
	if (is_cmd(cur_cmd->cmd) == 1) // si c'est une commande interne il l'execute
	{	
		cmd_exec(cur_cmd, env);  // poour executer sans utiliser fork sinon c'est chelouuuu
		exit(1);
	}
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
	// if (found_path(cur_cmd) == NULL)
	// {
	// 	printf("command not found: %s\n", cur_cmd->cmd);
	// 	val_ret = 127;
	// 	exit(127);
	// }
	execve(found_path(cur_cmd), args, NULL); // execute la commande en la cherchant dans le path
	perror("execve");
	exit(127);
	free(found_path(cur_cmd));
	free_tab(args);
	exit(1);
}


void	exec_pipe(t_cmd *cmd, t_env *env)
{
	int fd[2];
	pid_t pid;
	t_cmd	*cur_cmd;
	int pipe_precedent;
	int status;

	cur_cmd = cmd;
	pipe_precedent = -1;
	while (cur_cmd)
	{
		
		if (cur_cmd->next_cmd)
		{
			pipe(fd);  // pour cree un pipe
			if (pipe(fd) == -1)
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
			fd[1] = -1;
		if (found_path(cur_cmd) == NULL)
		{
			printf("command no88t found: %s\n", cur_cmd->cmd);
			val_ret = 127;
			return ;
		}
		pid = fork();  // cree un processus
		if (pid < 0)
		{
			perror("fork");
			if (pipe_precedent != -1)
				close(pipe_precedent);
			if (fd[1] != -1)
			{
				close(fd[0]);
				close(fd[1]);
			}
			return ;
		}
		if (pid == 0) // le processus enfant ou vont s executer les commandes
		{
			if (pipe_precedent != -1)
			{
				dup2(pipe_precedent, STDIN_FILENO);
				close(pipe_precedent);
			}
			if (fd[1] != -1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
			}
			if (is_cmd(cur_cmd->cmd) == 1)
				cmd_exec(cur_cmd, env);
			else
				exec_process(cur_cmd, cur_cmd->next_cmd, fd, env);
			exit(1);
		}
		if (pipe_precedent != -1)
		{
			close(pipe_precedent);
		}
		if (fd[1] != -1)
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
	while (wait(&status) > 0);  // attend que tout les process se termine, retourne -1 quand les process finissent
}
