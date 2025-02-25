/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:27:05 by nas               #+#    #+#             */
/*   Updated: 2025/02/25 10:14:35 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// la fonction qui va extraire toutes les commandes des arguments
char *recup_token(char *str, int *index)
{
    int i;
    int start, end;
    char c;
    char *str_recup;

    i = *index;
    while (str[i] && ft_isspace(str[i]))
        i++;
    
    if (!str[i])
        return NULL;
    if (str[i] == '"' || str[i] == '\'')
    {
        c = str[i];
        i++;
        start = i;
        while (str[i] && str[i] != c)
            i++;
        if (!str[i])
            return NULL;
        end = i;
        i++;
    }
    else
    {
        start = i;
        while (str[i] && !ft_isspace(str[i]) && str[i] != '<' && str[i] != '>' && str[i] != '|')
            i++;
        end = i;
    }

    *index = i;
    if (end <= start)
        return NULL;
    
    str_recup = ft_substr(str, start, end - start);
    return str_recup;
}



// analyse, decoupe et rempli les structures en fonction de ce qu'on recupere
void parsing(char *str, t_cmd *cmd)
{
    int i;
    char *token;
    t_redirection *new_redir;
    t_pipe  *pipe;

    i = 0;
    if (str == NULL || cmd == NULL)
        return ;

    cmd->cmd = NULL;
    cmd->arg = NULL;
    cmd->redirection = NULL;
    cmd->pipe = NULL;

    while (str[i])
    {
        while (str[i] && ft_isspace(str[i]))
            i++;
        if (str[i] == '<' || str[i] == '>')
        {
            new_redir = found_redirection(str, &i);
            if (new_redir)
                add_redirection(cmd, new_redir);
        }
        else if (str[i] == '|')
        {
            pipe = found_pipe(str, &i);
            if (pipe)
                add_pipe(cmd, pipe);
        }
        token = recup_token(str, &i);
        if (token)
        {
            if (cmd->cmd == NULL)
                cmd->cmd = token;
            else
                add_token(&cmd->arg, new_token(token));
        }
    }
}




