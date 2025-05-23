/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:38:40 by nas               #+#    #+#             */
/*   Updated: 2025/04/15 13:12:52 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_out(t_cmd *cmd, int fd)
{
	fd = open(cmd->redirection->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		g_val_ret = 1;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_in(t_cmd *cmd, int fd)
{
	fd = open(cmd->redirection->file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		g_val_ret = 1;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redir_append(t_cmd *cmd, int fd)
{
	fd = open(cmd->redirection->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		g_val_ret = 1;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
