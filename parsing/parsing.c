/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:27:05 by nas               #+#    #+#             */
/*   Updated: 2025/03/25 12:43:15 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// la fonction qui va extraire toutes les commandes des arguments
char *expand_var_at_position(char *str, int *pos, t_env *env)
{
    int start = *pos;
    int end = start + 1;
    char *var_name;
    char *var_value;
    char *result;
    int len_before, len_var, len_after;
    if (str[end] == '?')
    {
        char *val_ret_str = ft_itoa(val_ret);
        if (!val_ret_str)
            return ft_strdup(str);
            
        len_before = start;
        len_after = ft_strlen(str + start + 2);
        
        result = malloc(len_before + ft_strlen(val_ret_str) + len_after + 1);
        if (!result)
        {
            free(val_ret_str);
            return ft_strdup(str);
        }
        
        ft_memcpy(result, str, len_before);
        strcpy(result + len_before, val_ret_str);
        strcpy(result + len_before + ft_strlen(val_ret_str), str + start + 2);
        
        *pos = len_before + ft_strlen(val_ret_str);
        free(val_ret_str);
        return result;
    }
    while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
        end++;
    len_var = end - start - 1;
    if (len_var == 0)
        return ft_strdup(str);
    
    var_name = ft_substr(str, start + 1, len_var);
    if (!var_name)
        return NULL;
    var_value = get_env_value(env, var_name);
    free(var_name);
    if (!var_value)
        var_value = "";
    len_before = start;
    len_after = ft_strlen(str + end);
    result = malloc(len_before + ft_strlen(var_value) + len_after + 1);
    if (!result)
        return NULL;
    ft_memcpy(result, str, len_before);
    strcpy(result + len_before, var_value);
    strcpy(result + len_before + ft_strlen(var_value), str + end);
    *pos = len_before + ft_strlen(var_value);
    return result;
}

char *expand_variables(char *str, t_env *env)
{
    int i = 0;
    char quote_state = 0;
    char *result = ft_strdup(str);
    
    if (!result)
        return (NULL);
    
    while (result[i])
    {
        if (result[i] == '\'')
        {
            if (quote_state == 0)
                quote_state = '\'';
            else if (quote_state == '\'')
                quote_state = 0;
        }
        else if (result[i] == '"')
        {
            if (quote_state == 0)
                quote_state = '"';
            else if (quote_state == '"')
                quote_state = 0;
        }
        if (result[i] == '$' && quote_state != '\'')
        {
            char *expanded = expand_var_at_position(result, &i, env);
            if (!expanded)
                return (NULL);
            
            free(result);
            result = expanded;
            continue;
        }
        
        i++;
    }
    
    return (result);
}

char *process_quotes(char *str)
{
    int i = 0;
    int j = 0;
    char *result;
    char quote_state = 0;
    
    result = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!result)
        return (str);
    
    while (str[i])
    {
        if (str[i] == '\'')
        {
            if (quote_state == 0)
                quote_state = '\'';
            else if (quote_state == '\'')
                quote_state = 0;
            else if (quote_state == '"')
                result[j++] = str[i];
        }
        else if (str[i] == '"')
        {
            if (quote_state == 0)
                quote_state = '"';
            else if (quote_state == '"')
                quote_state = 0;
            else if (quote_state == '\'')
                result[j++] = str[i];
        }
        else
            result[j++] = str[i];
        i++;
    }
    result[j] = '\0';
    free(str);
    return (result);
}

char *recup_token(char *str, int *index, t_env *env)
{
    int i;
    int start;
    int end;
    char current_quote = 0;  // 0 = pas de quote, '\'' = simple quote, '"' = double quote
    char *str_recup;
    char *result;
    
    i = *index;
    while (str[i] && ft_isspace(str[i]))
        i++;   
    if (!str[i])
        return (NULL);
    start = i;
    while (str[i] && ((!ft_isspace(str[i]) || current_quote) && 
          ((str[i] != '<' && str[i] != '>' && str[i] != '|') || current_quote)))
    {
        if (!current_quote && (str[i] == '\'' || str[i] == '"'))
            current_quote = str[i];
        else if (current_quote && str[i] == current_quote)
            current_quote = 0;
        
        i++;
    }
    end = i;
    *index = i;
    if (end <= start)
        return (NULL);     
    str_recup = ft_substr(str, start, end - start);
    if (!str_recup)
        return (NULL);
    checkif2(str_recup, '"');
    checkif2(str_recup, '\'');
    // Traitement des variables d'environnement en tenant compte des quotes
    result = expand_variables(str_recup, env);
    free(str_recup);
    
    if (!result)
        return (NULL);
    result = process_quotes(result);   
    return (result);
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
    config_signals_exec();
    
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
    restore_signals();
}
