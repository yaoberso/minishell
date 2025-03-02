/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:38:40 by nas               #+#    #+#             */
/*   Updated: 2025/03/02 11:02:00 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redir_out(t_cmd *cmd, int fd)
{
	fd = open(cmd->redirection->file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // ouvre le fichier, le cree si il est inexistant et l'ecrase si il existe
	if (fd == -1)                                                  // 0644 c'est les droits d'acces comme chmod 777
	{
		perror("open");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_in(t_cmd *cmd, int fd)
{
	fd = open(cmd->redirection->file, O_RDONLY); // ouvre le fichier en lecture seule
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redir_append(t_cmd *cmd, int fd)
{
	fd = open(cmd->redirection->file, O_WRONLY | O_CREAT | O_APPEND, 0644); // ouvre el fichier, le cree si il exoste pas et ecrit a la fin si il existe
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_heredoc(t_cmd *cmd, int fd)
{
	fd = 
}
