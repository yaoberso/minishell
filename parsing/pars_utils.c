/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:00:08 by nas               #+#    #+#             */
/*   Updated: 2025/02/25 13:24:16 by nadahman         ###   ########.fr       */
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

void    add_pipe(t_cmd *cmd, t_pipe *pipe)
{
    t_pipe *tmp;
    
    if (cmd == NULL || pipe == NULL)
        return;
    if (cmd->pipe == NULL)
    {
        cmd->pipe = pipe;
        return;
    }
    else
    {
        tmp = cmd->pipe;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = pipe;
    }
}

t_pipe *found_pipe(char *str, int *index)
{
    t_pipe *pipe;
    
    pipe = malloc(sizeof(t_pipe));
    if (pipe == NULL)
        return (NULL);
    
    pipe->type = NULL;
    pipe->cmd_pipe = NULL;
    pipe->next = NULL;
    
    if (str[*index] == '|')
    {
        pipe->type = ft_strdup("|");
        (*index)++;
    }
    else
    {
        free(pipe);
        return (NULL);
    }
    if (pipe->type == NULL)
    {
        free(pipe);
        return (NULL);
    }
    while (str[*index] && ft_isspace(str[*index]))
        (*index)++;
    if (str[*index] == '\0' || str[*index] == '|' || str[*index] == '<' || str[*index] == '>')
    {
        printf("Error: apres le `|'\n");
        free(pipe->type);
        free(pipe);
        return (NULL);
    }
    pipe->cmd_pipe = recup_token(str, index);
    if (pipe->cmd_pipe == NULL)
    {
        free(pipe->type);
        free(pipe);
        return (NULL);
    }
    
    return (pipe);
}


// pour trouver une redirection, le *index c'est la position du caractere apres la redirection
t_redirection *found_redirection(char *str, int *index)
{
    t_redirection *redir = malloc(sizeof(t_redirection));
    
    if (redir == NULL)
        return (NULL);
    redir->next = NULL;
    if (str[*index] == '<')
    {
        if (str[*index + 1] == '<')
        {
            redir->type = ft_strdup("<<");
            *index = *index + 2;
        }
        else
        {
            redir->type = ft_strdup("<");
            *index = *index + 1;
        }
    }
    else if (str[*index] == '>')
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
    }
    if (redir->type == NULL)
    {
        free(redir);
        return (NULL);
    }
    while (str[*index] && ft_isspace(str[*index]))
        (*index)++;
    if (str[*index] == '\0' || ft_isspace(str[*index]) || str[*index] == '>' || str[*index] == '<' || str[*index] == '|')
    {
        printf("Error : apres la redirection\n");
        return (NULL);
    }
    redir->file = recup_token(str, index);
    if (redir->file && (redir->file[0] == '>' || redir->file[0] == '<' || redir->file[0] == '|'))
    {
        printf("Error : Nom de fichier invalide\n");
        free(redir->type);
        free(redir->file);
        free(redir);
        return (NULL);
    }
    if (redir->file == NULL)
    {
        free(redir->type);
        free(redir);
        return (NULL);
    }
    return (redir);
}





