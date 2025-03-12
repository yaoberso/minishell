/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:34:51 by nas               #+#    #+#             */
/*   Updated: 2025/03/12 11:37:31 by nas              ###   ########.fr       */
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
   		printf("%s: fonctionne pas dans un pipe\n", cur_cmd->cmd);    // a voir si j e garde selon le comprortement de bash
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
	if (found_path(cur_cmd) == NULL)
	{
		printf("command not found: %s\n", cur_cmd->cmd);
		exit(127);
	}
	execve(found_path(cur_cmd), args, NULL); // execute la commande en la cherchant dans le path
	perror("execve");
	free(found_path(cur_cmd));
	free_tab(args);
	exit(1);
}
// void	create_pipe(int fd[2], t_cmd *next_cmd)
// {
// 	if (next_cmd == NULL)
// 		return ;
// 	if (next_cmd && pipe(fd) == -1)
// 	{
// 		perror("pipe");
// 		exit(1);
// 	}
// }

// void gerer_process(pid_t pid, int fd[2], t_cmd **cur_cmd)
// {
//     (void)pid;
//     if (fd[1] != -1)
//         close(fd[1]); 
//     if (fd[0] != -1 && *cur_cmd && (*cur_cmd)->prev_cmd)
//         close(fd[0]);
//     if (*cur_cmd)
//         *cur_cmd = (*cur_cmd)->next_cmd;
// }


// void	exec_pipe(t_cmd *cmd, t_env *env)
// {
// 	pid_t	pid;
// 	int		fd[2] = {-1, -1};
// 	t_cmd	*cur_cmd;

// 	cur_cmd = cmd;
// 	while (cur_cmd)
// 	{
// 		create_pipe(fd, cur_cmd->next_cmd); // cree un pipe si il y a une commande apres
// 		pid = fork(); // pour cree un processus
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			exit(1);
// 		}
// 		if (pid == 0)
// 			exec_process(cur_cmd, cur_cmd->next_cmd, fd, env); // execute la commande dans le process enfant
// 		else
// 			gerer_process(pid, fd, &cur_cmd); // gere les processus
// 	}
// 	if (fd[1] != -1)
// 		close(fd[1]);
// 	if (fd[0] != -1)
// 		close(fd[0]);

// 	while (wait(NULL) > 0); // attendre que le processus enfant se termine
// }

void	exec_pipe(t_cmd *cmd, t_env *env)
{
	int fd[2] = {-1, -1};
	pid_t pid;
	t_cmd *cur_cmd;
	int prev_pipe;
	int status;
	
	cur_cmd = cmd;
	prev_pipe = -1;
	while (cur_cmd)
	{
		if (cur_cmd->next_cmd)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				if (prev_pipe != -1)
					close(prev_pipe);
				return ;
			}
		}
		else
			fd[1] = -1;
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			if (prev_pipe != -1)
				close(prev_pipe);
			if (fd[1] != 1)
			{
				close(fd[1]);
				close(fd[0]);
			}
			return ;
		}
		if (pid == 0)
		{
			if (prev_pipe != -1)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
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
		
		if (prev_pipe != -1)
			close(prev_pipe);
		if (fd[1] != -1)
		{
			close(fd[1]);
			prev_pipe = fd[0];
		}
		cur_cmd = cur_cmd->next_cmd;
	}
	if (prev_pipe != -1)
		close(prev_pipe);
	
	while (wait(&status) > 0);
}


