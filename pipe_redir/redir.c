/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:35:39 by nas               #+#    #+#             */
/*   Updated: 2025/03/18 12:58:41 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_redir(t_cmd *cmd)
{
	int fd;
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
			redir_heredoc(cmd);
			cmd->redirection = tmp;
		}
		current = current->next;
	}
}
