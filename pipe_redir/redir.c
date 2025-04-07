/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:35:39 by nas               #+#    #+#             */
/*   Updated: 2025/04/07 16:06:36 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exec_redir(t_cmd *cmd)
// {
// 	int				fd;
// 	t_redirection	*current;
// 	t_redirection	*tmp;

// 	current = cmd->redirection;
// 	while (current)
// 	{
// 		fd = -1;
// 		if (ft_strcmp(current->type, ">") == 0)
// 			redir_out(cmd, fd);
// 		else if (ft_strcmp(current->type, "<") == 0)
// 			redir_in(cmd, fd);
// 		else if (ft_strcmp(current->type, ">>") == 0)
// 			redir_append(cmd, fd);
// 		else if (ft_strcmp(current->type, "<<") == 0)
// 		{
// 			tmp = cmd->redirection;
// 			cmd->redirection = current;
// 			redir_heredoc(cmd);
// 			cmd->redirection = tmp;
// 		}
// 		if (val_ret != 0)
// 			return ;
// 		current = current->next;
// 	}
// }

void	exec_redir(t_cmd *cmd)
{
	int				fd;
	t_redirection	*current;

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
		if (val_ret != 0)
			return ;
		current = current->next;
	}
}

int	exec_heredocs(t_cmd *cmd)
{
	t_redirection	*current;
	t_redirection	*tmp;
	int heredoc_found;

	current = cmd->redirection;
	while (current)
	{
		if (ft_strcmp(current->type, "<<") == 0)
		{
			tmp = cmd->redirection;
			cmd->redirection = current;
			redir_heredoc(cmd);
			cmd->redirection = tmp;
			heredoc_found = 1;
		}
		if (val_ret != 0)
			return (-1);
		current = current->next;
	}
	if (heredoc_found == 1)
		return (0);
	else
		return (-1);	
}

