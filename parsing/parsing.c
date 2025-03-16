/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:27:05 by nas               #+#    #+#             */
/*   Updated: 2025/03/16 12:39:55 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// la fonction qui va extraire toutes les commandes des arguments
char *recup_token(char *str, int *index, t_env *env)
{
    int i;
    int start;
    int end;
    char c;
    char *str_recup;
    char *envexp;
    char *arg;
    char *env_value;
    
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
    if (!str_recup)
        return NULL;
    i = 0;
    while(str_recup[i] != '\0')
    {
        if (str_recup[i] == '$' && str_recup[i+1] != '\0')
        {
            if(str_recup[i + 1] == '?')
            {
                printf("%i\n", val_ret);
                free(str_recup);
                return (NULL);
            }
            start = i;
            i++;
            end = 0;
            while(str_recup[i+end] != '\0' && str_recup[i+end] != ' ' &&
                  str_recup[i+end] != '$' && str_recup[i+end] != '\'' &&
                  str_recup[i+end] != '"')
                end++;
            if (end == 0)
            {
                i++;
                continue;
            }
            envexp = ft_substr(str_recup, i, end);
            if (!envexp)
            {
                // return str_recup;
                free(str_recup);
                return (NULL);
            }
            env_value = get_env_value(env, envexp);
            free(envexp);
            envexp = NULL;
            if (env_value)
            {
                int new_len = ft_strlen(str_recup) - end + ft_strlen(env_value) + 1;
                arg = malloc(sizeof(char) * new_len);
                if (!arg)
                {
                    // return str_recup;
                    free(str_recup);
                    return (NULL);
                }
                ft_memcpy(arg, str_recup, start);
                arg[start] = '\0';
                strcat(arg, env_value);
                strcat(arg, str_recup + i + end);    
                free(str_recup);
                str_recup = arg;
                i = start + ft_strlen(env_value);
            }
            else
            {
                ft_memmove(str_recup + start, str_recup + i + end,
                         ft_strlen(str_recup + i + end) + 1);
                i = start;
            }
        }
        else
            i++;
    }
    
    return str_recup;
}

// analyse, decoupe et rempli les structures en fonction de ce qu'on recupere
void parsing(char *str, t_cmd *cmd, t_env *env)
{
    int i;
    char *token;
    t_redirection *new_redir;
    t_cmd *next_cmd;
    
    i = 0;
    if (str == NULL || cmd == NULL)
        return;
    cmd->cmd = NULL;
    cmd->arg = NULL;
    cmd->redirection = NULL;
    cmd->next_cmd = NULL;
    
    while (str[i])
    {
        while (str[i] && ft_isspace(str[i]))
            i++;
        if (!str[i])
            break ;
        if (str[i] == '<' || str[i] == '>')
        {
            new_redir = found_redirection(str, &i, env);
            if (new_redir)
                add_redirection(cmd, new_redir);
        }
        else if (str[i] == '|')
        {
            next_cmd = found_next_cmd(str, &i, env);
            if (next_cmd)
            {
                add_next_cmd(cmd, next_cmd);
                next_cmd->prev_cmd = cmd;
            }
            break ;
        }
        else
        {
            token = recup_token(str, &i, env);
            if (token)
            {
                if (cmd->cmd == NULL)
                    cmd->cmd = token;
                else
                    add_token(&cmd->arg, new_token(token));
            }
        }
    }
}
