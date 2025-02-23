/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:00:08 by nas               #+#    #+#             */
/*   Updated: 2025/02/23 18:42:30 by nas              ###   ########.fr       */
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
    redir->file = recup_token(str, index);
    if (redir->file == NULL)
    {
        free(redir->type);
        free(redir);
        return (NULL);
    }
    return (redir);
}





