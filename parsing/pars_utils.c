/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:00:08 by nas               #+#    #+#             */
/*   Updated: 2025/04/01 09:56:51 by yann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pour creer un nouveau token en fonction de ce qu'on recupere 
t_token	*new_token(char *str)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->value = ft_strdup(str);
	token->next = NULL;
	return (token);
}

// pour ajouter un token a la fin de la liste
void add_token(t_token **head, t_token *new)
{
	t_token *tmp;

	if (head == NULL || new == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}
// pour ajouter une redirection qu'on aura exrtait, a la fin de la liste
void add_redirection(t_cmd *cmd, t_redirection *new_redir)
{
    t_redirection *tmp;

    if (cmd == NULL || new_redir == NULL)
        return;
    if (cmd->redirection == NULL)
    {
        cmd->redirection = new_redir;
        return;
    }
    else
    {
        tmp = cmd->redirection;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new_redir;
    }
}

void add_next_cmd(t_cmd *cmd, t_cmd *next_cmd)
{
    t_cmd *tmp;
    
    if (cmd == NULL || next_cmd == NULL)
        return;
    
    if (cmd->next_cmd == NULL)
    {
        cmd->next_cmd = next_cmd;
        return;
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
void init_next_cmd(t_cmd *next_cmd)
{
	next_cmd->cmd = NULL;
	next_cmd->arg = NULL;
	next_cmd->redirection = NULL;
	next_cmd->next_cmd = NULL;
}

int check_pipe_syntax(char *str, int *index, t_cmd *next_cmd)
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
		free(next_cmd);
		return (0);
	}
	return (1);
}

int handle_cmd_token(t_cmd *next_cmd, char *str, int *index, t_env *env)
{
	next_cmd->cmd = recup_token(str, index, env);
	if (next_cmd->cmd == NULL)
	{
		free(next_cmd);
		return (0);
	}
	return (1);
}

int process_redirection(t_cmd *next_cmd, char *str, int *index, t_env *env)
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

int process_pipe(t_cmd *next_cmd, char *str, int *index, t_env *env)
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

int process_argument(t_cmd *next_cmd, char *str, int *index, t_env *env)
{
	char	*token;

	token = recup_token(str, index, env);
	if (token)
		add_token(&next_cmd->arg, new_token(token));
	else
	{
		free_cmd(next_cmd);
		return (0);
	}
	return (1);
}

t_cmd *found_next_cmd(char *str, int *index, t_env *env)
{
	t_cmd	*next_cmd;

	next_cmd = malloc(sizeof(t_cmd));
	if (next_cmd == NULL)
		return (NULL);
	init_next_cmd(next_cmd);
	if (!check_pipe_syntax(str, index, next_cmd))
		return (NULL);
	if (!handle_cmd_token(next_cmd, str, index, env))
		return (NULL);
	while (str[*index])
	{
		while (str[*index] && ft_isspace(str[*index]))
			(*index)++;
		if (!str[*index])
			break ;
		if (str[*index] == '<' || str[*index] == '>')
		{
			if (!process_redirection(next_cmd, str, index, env))
				return (NULL);
		}
		else if (str[*index] == '|')
		{
			if (!process_pipe(next_cmd, str, index, env))
				return (NULL);
			break ;
		}
		else if (!process_argument(next_cmd, str, index, env))
			return (NULL);
	}
	return (next_cmd);
}

/* Part 2: found_redirection split into multiple functions */
void init_redirection(t_redirection *redir)
{
	redir->type = NULL;
	redir->file = NULL;
	redir->next = NULL;
}

int handle_heredoc(t_redirection *redir, char *str, int *index, t_env *env)
{
	redir->type = ft_strdup("<<");
	*index = *index + 2;
	while (str[*index] && ft_isspace(str[*index]))
		(*index)++;
	if (!str[*index] || str[*index] == '>' || str[*index] == '<' 
		|| str[*index] == '|')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		free(redir->type);
		free(redir);
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

int handle_input_redir(t_redirection *redir, int *index)
{
	redir->type = ft_strdup("<");
	*index = *index + 1;
	return (1);
}

int handle_output_redir(t_redirection *redir, char *str, int *index)
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

int get_redir_file(t_redirection *redir, char *str, int *index, t_env *env)
{
	while (str[*index] && ft_isspace(str[*index]))
		(*index)++;
	if (str[*index] == '\0' || ft_isspace(str[*index]) || str[*index] == '>' 
		|| str[*index] == '<' || str[*index] == '|')
	{
		printf("bash: syntax error near unexpected token `newline'\n");
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

int check_redir_file(t_redirection *redir)
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

t_redirection *found_redirection(char *str, int *index, t_env *env)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (redir == NULL)
		return (NULL);
	init_redirection(redir);
	if (str[*index] == '<')
	{
		if (str[*index + 1] == '<')
		{
			if (!handle_heredoc(redir, str, index, env))
				return (NULL);
			return (redir);
		}
		else if (!handle_input_redir(redir, index))
			return (NULL);
	}
	else if (str[*index] == '>' && !handle_output_redir(redir, str, index))
		return (NULL);
	if (redir->type == NULL)
	{
		free(redir);
		return (NULL);
	}
	if (!get_redir_file(redir, str, index, env))
		return (NULL);
	if (!check_redir_file(redir))
		return (NULL);
	return (redir);
}
