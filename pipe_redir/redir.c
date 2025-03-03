/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:35:39 by nas               #+#    #+#             */
/*   Updated: 2025/03/03 10:17:31 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	exec_redir(t_cmd *cmd)
{
	int fd = -1;
	
	if (cmd->redirection)
	{
		if (ft_strcmp(cmd->redirection->type, ">") == 0)
			redir_out(cmd, fd);
		else if (ft_strcmp(cmd->redirection->type, "<") == 0)	
			redir_in(cmd, fd);
		else if (ft_strcmp(cmd->redirection->type, ">>") == 0)
			redir_append(cmd, fd);
		// else if (ft_strcmp(cmd->redirection->type, "<<") == 0)
		// 	redir_heredoc(cmd, fd);
	}
}
