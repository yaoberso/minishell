/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:01:50 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/23 14:27:36 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_next_cmd(t_cmd *cmd, t_cmd *next_cmd)
{
	t_cmd	*tmp;

	if (cmd == NULL || next_cmd == NULL)
		return ;
	if (cmd->next_cmd == NULL)
	{
		cmd->next_cmd = next_cmd;
		return ;
	}
	else
	{
		tmp = cmd->next_cmd;
		while (tmp->next_cmd != NULL)
			tmp = tmp->next_cmd;
		tmp->next_cmd = next_cmd;
	}
}

/* Part 1: found_next_cmd split into multiple functions */
void	init_next_cmd(t_cmd *next_cmd)
{
	next_cmd->cmd = NULL;
	next_cmd->arg = NULL;
	next_cmd->redirection = NULL;
	next_cmd->next_cmd = NULL;
	next_cmd->prev_cmd = NULL;
	next_cmd->heredoc_fd = -1;
	next_cmd->save_stdin = -1;
	next_cmd->std = malloc(sizeof(t_std));
	if (next_cmd->std == NULL)
	{
		free(next_cmd);
		return ;
	}
	next_cmd->std->save_instd = -1;
	next_cmd->std->save_outstd = -1;
	next_cmd->std->original_stdin = -1;
	next_cmd->if_error = 0;
	next_cmd->in_child = 0;
	next_cmd->env = NULL;
}

int	check_pipe_syntax(char *str, int *index, t_cmd *next_cmd)
{
	if (str[*index] == '|')
		(*index)++;
	else
	{
		free(next_cmd);
		return (0);
	}
	while (str[*index] && ft_isspace(str[*index]))
		(*index)++;
	if (str[*index] == '\0' || str[*index] == '|' || str[*index] == '<'
		|| str[*index] == '>')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		ms_status(2);
		free_cmd(next_cmd);
		return (0);
	}
	return (1);
}

int	handle_cmd_token(t_cmd *next_cmd, char *str, int *index, t_env *env)
{
	next_cmd->cmd = recup_token(str, index, env);
	if (next_cmd->cmd == NULL)
	{
		free(next_cmd);
		return (0);
	}
	return (1);
}

int	process_redirection(t_cmd *next_cmd, char *str, int *index, t_env *env)
{
	t_redirection	*new_redir;

	new_redir = found_redirection(str, index, env);
	if (new_redir)
		add_redirection(next_cmd, new_redir);
	else
	{
		free_cmd(next_cmd);
		return (0);
	}
	return (1);
}
