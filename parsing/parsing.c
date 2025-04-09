/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:27:05 by nas               #+#    #+#             */
/*   Updated: 2025/04/09 18:42:39 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*recup_token(char *str, int *index, t_env *env)
{
	int		start;
	int		end;
	char	*str_recup;

	find_token_bounds(str, &start, &end, index);
	if (end <= start)
		return (NULL);
	str_recup = ft_substr(str, start, end - start);
	return (process_token(str_recup, env));
}

void	initialize_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	cmd->cmd = NULL;
	cmd->arg = NULL;
	cmd->redirection = NULL;
	cmd->next_cmd = NULL;
}

void	process_single_token(char *token, t_cmd *cmd)
{
	if (token)
	{
		if (cmd->cmd == NULL)
		{
			cmd->cmd = token;
		}
		else	
			add_token(&cmd->arg, new_token(token));
	}
}

int	process_parsing_char(char *str, int *i, t_cmd *cmd, t_env *env)
{
	t_redirection	*new_redir;
	t_cmd			*next_cmd;

	if (str[*i] == '<' || str[*i] == '>')
	{
		new_redir = found_redirection(str, i, env);
		if (new_redir)
			add_redirection(cmd, new_redir);
		else
			cmd->if_error = 1;
	}
	else if (str[*i] == '|')
	{
		next_cmd = found_next_cmd(str, i, env);
		if (next_cmd)
		{
			add_next_cmd(cmd, next_cmd);
			next_cmd->prev_cmd = cmd;
		}
		else
			cmd->if_error = 1;
		return (1);
	}
	else
	{
		processe_token(str, i, cmd, env);
	}
	return (0);
}

void	parsing(char *str, t_cmd *cmd, t_env *env)
{
	int	i;

	i = 0;
	if (str == NULL || cmd == NULL)
		return ;
	initialize_cmd(cmd);
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		if (process_parsing_char(str, &i, cmd, env))
			break ;
	}
}
