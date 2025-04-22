/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils9.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:01:57 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/22 11:16:23 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirection(t_redirection *redir)
{
	redir->type = NULL;
	redir->file = NULL;
	redir->next = NULL;
	redir->redir_error = 0;
	redir->heredoc_delim = NULL;
}

int	handle_heredoc(t_redirection *redir, char *str, int *index, t_env *env)
{
	redir->type = ft_strdup("<<");
	*index = *index + 2;
	while (str[*index] && ft_isspace(str[*index]))
		(*index)++;
	if (!str[*index] || str[*index] == '>' || str[*index] == '<'
		|| str[*index] == '|')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		ms_status(2);
		redir->redir_error = 1;
		free(redir->type);
		// free(redir);
		return (0);
	}
	redir->heredoc_delim = recup_token(str, index, env);
	if (redir->heredoc_delim == NULL)
	{
		free(redir->type);
		free(redir);
		return (0);
	}
	return (1);
}

int	handle_input_redir(t_redirection *redir, int *index)
{
	redir->type = ft_strdup("<");
	*index = *index + 1;
	return (1);
}

int	handle_output_redir(t_redirection *redir, char *str, int *index)
{
	if (str[*index + 1] == '>')
	{
		redir->type = ft_strdup(">>");
		*index = *index + 2;
	}
	else
	{
		redir->type = ft_strdup(">");
		*index = *index + 1;
	}
	return (1);
}

int	get_redir_file(t_redirection *redir, char *str, int *index, t_env *env)
{
	while (str[*index] && ft_isspace(str[*index]))
		(*index)++;
	if (str[*index] == '\0' || ft_isspace(str[*index]) || str[*index] == '>'
		|| str[*index] == '<' || str[*index] == '|')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		ms_status(2);
		redir->redir_error = 1;
		free(redir->type);
		free(redir);
		return (0);
	}
	redir->file = recup_token(str, index, env);
	if (redir->file == NULL)
	{
		free(redir->type);
		free(redir);
		return (0);
	}
	return (1);
}
