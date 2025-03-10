/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:35:39 by nas               #+#    #+#             */
/*   Updated: 2025/03/10 10:01:44 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_redir(t_cmd *cmd)
{
	int fd;
	int heredoc_fd[2];
	t_redirection *current;
	t_redirection *tmp;
	
	current = cmd->redirection;
	while (current)
	{
		fd = -1;
		if (ft_strcmp(current->type, ">") == 0)
			redir_out(cmd, fd);
		else if (ft_strcmp(current->type, "<") == 0)	
			redir_in(cmd, fd);
		else if (ft_strcmp(current->type, ">>") == 0)
			redir_append(cmd, fd);
		else if (ft_strcmp(current->type, "<<") == 0)
		{
			tmp = cmd->redirection;
			cmd->redirection = current;
			redir_heredoc(cmd, heredoc_fd);
			cmd->redirection = tmp;
		}
		current = current->next;
	}
}
