/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:00:08 by nas               #+#    #+#             */
/*   Updated: 2025/03/11 13:22:35 by nadahman         ###   ########.fr       */
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

t_cmd *found_next_cmd(char *str, int *index)
{
    t_cmd *next_cmd;
    t_redirection *new_redir;
    t_cmd *another_cmd;
    char *token;
    
    next_cmd = malloc(sizeof(t_cmd));
    if (next_cmd == NULL)
        return (NULL);
    next_cmd->cmd = NULL;
    next_cmd->arg = NULL;
    next_cmd->redirection = NULL;
    next_cmd->next_cmd = NULL;
    if (str[*index] == '|')
    {
        (*index)++;
    }
    else
    {
        free(next_cmd);
        return (NULL);
    }
    while (str[*index] && ft_isspace(str[*index]))
        (*index)++;
    if (str[*index] == '\0' || str[*index] == '|' || str[*index] == '<' || str[*index] == '>')
    {
        printf("Error: apres le `|'\n");
        free(next_cmd);
        return (NULL);
    }
    next_cmd->cmd = recup_token(str, index);
    if (next_cmd->cmd == NULL)
    {
        free(next_cmd);
        return (NULL);
    }
    while (str[*index])
    {
        while (str[*index] && ft_isspace(str[*index]))
            (*index)++;
        if (!str[*index])
            break ; 
        if (str[*index] == '<' || str[*index] == '>')
        {
            new_redir = found_redirection(str, index);
            if (new_redir)
                add_redirection(next_cmd, new_redir);
            else
                break ;
        }
        else if (str[*index] == '|')
        {
            another_cmd = found_next_cmd(str, index);
            if (another_cmd)
                add_next_cmd(next_cmd, another_cmd);
            break ;
        }
        else
        {
            token = recup_token(str, index);
            if (token)
                add_token(&next_cmd->arg, new_token(token));
        }
    }
    return (next_cmd);
}


// pour trouver une redirection, le *index c'est la position du caractere apres la redirection
t_redirection *found_redirection(char *str, int *index)
{
    t_redirection *redir = malloc(sizeof(t_redirection));
    
    if (redir == NULL)
        return (NULL);
    
    redir->type = NULL;
    redir->file = NULL;
    redir->next = NULL;

    if (str[*index] == '<')
    {
        if (str[*index + 1] == '<')
        {
            redir->type = ft_strdup("<<");
            *index = *index + 2;
            while (str[*index] && ft_isspace(str[*index]))
                (*index)++;
            if (!str[*index] || str[*index] == '>' || str[*index] == '<' || str[*index] == '|')
            {
                printf("Error : délimiteur de heredoc manquant après `<<`\n");
                free(redir->type);
                free(redir);
                return (NULL);
            }
            redir->heredoc_delim = recup_token(str, index);
            if (redir->heredoc_delim == NULL)
            {
                free(redir->type);
                free(redir);
                return (NULL);
            }
            return (redir);
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
        free(redir->type);
        free(redir);
        return (NULL);
    }
    redir->file = recup_token(str, index);
    if (redir->file == NULL)
    {
        free(redir->type);
        free(redir);
        return (NULL);
    }
    if (redir->file[0] == '>' || redir->file[0] == '<' || redir->file[0] == '|')
    {
        printf("Error : Nom de fichier invalide\n");
        free(redir->type);
        free(redir->file);
        free(redir);
        return (NULL);
    }

    return (redir);
}
