/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:35:39 by nas               #+#    #+#             */
/*   Updated: 2025/03/19 17:45:56 by nas              ###   ########.fr       */
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


// void	exec_redir(t_cmd *cmd)
// {
// 	int fd;
// 	t_redirection *current;
	
// 	current = cmd->redirection;
// 	while (current)
// 	{
// 		fd = -1;
// 		if (ft_strcmp(current->type, ">") == 0)
// 		{
// 			fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (fd == -1)
// 			{
// 				perror("open");
// 				exit(1);
// 			}
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		else if (ft_strcmp(current->type, "<") == 0)
// 		{
// 			fd = open(current->file, O_RDONLY);
// 			if (fd == -1)
// 			{
// 				perror("open");
// 				exit(1);
// 			}
// 			dup2(fd, STDIN_FILENO);
// 			close(fd);
// 		}
// 		else if (ft_strcmp(current->type, ">>") == 0)
// 		{
// 			fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (fd == -1)
// 			{
// 				perror("open");
// 				exit(1);
// 			}
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		else if (ft_strcmp(current->type, "<<") == 0)
// 		{
// 			// Nous devons stocker le délimiteur du heredoc dans la structure
// 			// et l'utiliser dans la fonction read_heredoc
// 			cmd->redirection->heredoc_delim = current->heredoc_delim; // ou current->file si c'est là que le délimiteur est stocké
// 			if (redir_heredoc(cmd) != 0)
// 			{
// 				// Gérer l'erreur si nécessaire
// 				exit(1);
// 			}
// 		}
// 		current = current->next;
// 	}
// }