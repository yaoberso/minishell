/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:17 by nas               #+#    #+#             */
/*   Updated: 2025/03/03 12:14:17 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pour convertir la liste chainé des arguments en tableau de chaine de caracteres pour utuiliser execve
char	**get_args(t_cmd *cmd)
{
	t_token *token;
	char **args;
	int count;
	int	i;

	token = cmd->arg;
	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	args = malloc(sizeof(char *) * (count + 2));
	if (args == NULL)
		return (NULL);
	args[0] = cmd->cmd;
	token = cmd->arg;
	i = 1;
	while (token)
	{
		args[i++] = token->value;
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

void	free_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	count_cmd(t_cmd *cmd)
{
	int		count;
	t_cmd	*tmp;

	count = 0;
	tmp = cmd;
	while (tmp)
	{
		count++;
		tmp = tmp->next_cmd;
	}
	return (count);
}


void	redir_stdout(int fd[2], t_cmd *next_cmd)
{
	if (next_cmd)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

void redir_stdin(int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}