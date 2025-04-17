/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils8.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:01:53 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/10 10:11:19 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_pipe(t_cmd *next_cmd, char *str, int *index, t_env *env)
{
	t_cmd	*another_cmd;

	another_cmd = found_next_cmd(str, index, env);
	if (another_cmd)
	{
		add_next_cmd(next_cmd, another_cmd);
		another_cmd->prev_cmd = next_cmd;
	}
	else
	{
		free_cmd(next_cmd);
		return (0);
	}
	return (1);
}

int	process_argument(t_cmd *next_cmd, char *str, int *index, t_env *env)
{
	char	*token;

	token = recup_token(str, index, env);
	if (token)
	{
		add_token(&next_cmd->arg, new_token(token));
		free(token);
	}
	else
	{
		free_cmd(next_cmd);
		return (0);
	}
	return (1);
}

int	handle_cmd_start(t_cmd *next_cmd, char *str, int *index, t_env *env)
{
	if (!check_pipe_syntax(str, index, next_cmd))
		return (0);
	if (!handle_cmd_token(next_cmd, str, index, env))
		return (0);
	return (1);
}

int	handle_token(t_cmd *next_cmd, char *str, int *index, t_env *env)
{
	if (str[*index] == '<' || str[*index] == '>')
	{
		if (!process_redirection(next_cmd, str, index, env))
			return (0);
	}
	else if (str[*index] == '|')
	{
		if (!process_pipe(next_cmd, str, index, env))
			return (0);
		return (2);
	}
	else if (!process_argument(next_cmd, str, index, env))
		return (0);
	return (1);
}

t_cmd	*found_next_cmd(char *str, int *index, t_env *env)
{
	t_cmd	*next_cmd;
	int		result;

	next_cmd = malloc(sizeof(t_cmd));
	if (next_cmd == NULL)
		return (NULL);
	init_next_cmd(next_cmd);
	if (!handle_cmd_start(next_cmd, str, index, env))
		return (NULL);
	while (str[*index])
	{
		while (str[*index] && ft_isspace(str[*index]))
			(*index)++;
		if (!str[*index])
			break ;
		result = handle_token(next_cmd, str, index, env);
		if (result == 0)
			return (NULL);
		if (result == 2)
			break ;
	}
	return (next_cmd);
}
