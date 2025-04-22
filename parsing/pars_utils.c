/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:00:08 by nas               #+#    #+#             */
/*   Updated: 2025/04/22 10:51:06 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_file(t_redirection *redir)
{
	if (redir->file[0] == '>' || redir->file[0] == '<' || redir->file[0] == '|')
	{
		printf("bash: : No such file or directory\n");
		free(redir->type);
		free(redir->file);
		free(redir);
		return (0);
	}
	return (1);
}

int	handle_redirection_type(t_redirection *redir, char *str, int *index,
		t_env *env)
{
	if (str[*index] == '<')
	{
		if (str[*index + 1] == '<')
		{
			if (!handle_heredoc(redir, str, index, env))
				return (0);
			return (2);
		}
		else if (!handle_input_redir(redir, index))
			return (0);
	}
	else if (str[*index] == '>' && !handle_output_redir(redir, str, index))
		return (0);
	return (1);
}

int	validate_redirection(t_redirection *redir, char *str, int *index,
		t_env *env)
{
	if (redir->type == NULL)
		return (0);
	if (!get_redir_file(redir, str, index, env))
		return (0);
	if (!check_redir_file(redir))
		return (0);
	return (1);
}

t_redirection	*found_redirection(char *str, int *index, t_env *env)
{
	t_redirection	*redir;
	int				result;

	redir = malloc(sizeof(t_redirection));
	if (redir == NULL)
		return (NULL);
	init_redirection(redir);
	result = handle_redirection_type(redir, str, index, env);
	if (result == 0)
		return (NULL);
	if (result == 2)
		return (redir);
	if (!validate_redirection(redir, str, index, env))
	{
		return (NULL);
	}
	return (redir);
}

int	handle_pipe(t_cmd *cmd, char *str, int *i, t_env *env)
{
	t_cmd	*next_cmd;

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
