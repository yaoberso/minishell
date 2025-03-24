/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:27:05 by nas               #+#    #+#             */
/*   Updated: 2025/03/24 11:11:23 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// la fonction qui va extraire toutes les commandes des arguments
// char *recup_token(char *str, int *index, t_env *env)
// {
//     int i;
//     int start;
//     int end;
//     char c;
//     char *str_recup;
//     char *envexp;
//     char *arg;
//     char *env_value;
//     char *val_ret_str;
//     int new_len;
//     int simple_quote;
//     int double_quote;
    
//     i = *index;
//     simple_quote = 0;
//     double_quote = 0;
    
//     while (str[i] && ft_isspace(str[i]))
//         i++;
        
//     if (!str[i])
//         return (NULL);
        
//     if (str[i] == '"' || str[i] == '\'')
//     {
//         if (str[i] == '"')
//         {
//             double_quote = 1;
//             checkif2(str, '"');
//         }
//         else
//         {
//             simple_quote = 1;
//             checkif2(str, '\'');
//         }
//         c = str[i];
//         i++;
//         start = i;
//         while (str[i] && str[i] != c)
//             i++;
//         if (!str[i])
//             return (NULL);
//         end = i;
//         i++;
//     }
//     else
//     {
//         start = i;
//         while (str[i] && !ft_isspace(str[i]) && str[i] != '<' && str[i] != '>' && str[i] != '|')
//             i++;
//         end = i;
//     }
    
//     *index = i;
    
//     if (end <= start)
//         return (NULL);
        
//     str_recup = ft_substr(str, start, end - start);
//     if (!str_recup)
//         return (NULL);
        
//     i = 0;
//     while (str_recup[i] != '\0')
//     {
//         if (str_recup[i] == '$' && str_recup[i + 1] != '\0' && only_simple_quote(str_recup, double_quote) == 0)
//         {
//             if (str_recup[i + 1] == '?')
//             {
//                 val_ret_str = ft_itoa(val_ret);
//                 if (!val_ret_str)
//                     return (str_recup);
//                 new_len = ft_strlen(str_recup) - 2 + ft_strlen(val_ret_str) + 1;
//                 arg = malloc(sizeof(char) * new_len);
//                 if (!arg)
//                 {
//                     free(val_ret_str);
//                     return (str_recup);
//                 }
//                 ft_memcpy(arg, str_recup, i);
//                 arg[i] = '\0';
//                 strcat(arg, val_ret_str);
//                 strcat(arg, str_recup + i + 2);
//                 free(val_ret_str);
//                 free(str_recup);
//                 str_recup = arg;
//                 i += ft_strlen(val_ret_str);
//                 continue;
//             }
//             start = i;
//             i++;
//             end = 0;
//             while (str_recup[i + end] != '\0' && str_recup[i + end] != ' ' &&
//                 str_recup[i + end] != '$' && str_recup[i + end] != '\'' &&
//                 str_recup[i + end] != '"')
//                 end++;
//             if (end == 0)
//             {
//                 i++;
//                 continue;
//             }
//             envexp = ft_substr(str_recup, i, end);
//             if (!envexp)
//                 return (str_recup);
//             env_value = get_env_value(env, envexp);
//             free(envexp);
//             if (env_value)
//             {
//                 new_len = ft_strlen(str_recup) - end + ft_strlen(env_value) + 1;
//                 arg = malloc(sizeof(char) * new_len);
//                 if (!arg)
//                     return (str_recup);
//                 ft_memcpy(arg, str_recup, start);
//                 arg[start] = '\0';
//                 strcat(arg, env_value);
//                 strcat(arg, str_recup + i + end);
//                 free(str_recup);
//                 str_recup = arg;
//                 i = start + ft_strlen(env_value);
//             }
//             else
//             {
//                 ft_memmove(str_recup + start, str_recup + i + end,
//                     ft_strlen(str_recup + i + end) + 1);
//                 i = start;
//             }
//         }
//         else
//         {
//             i++;
//             if(double_quote == 0 && simple_quote == 0 && str_recup[i] == '\'')
//             {
//                 i++;
//                 while(str_recup[i] != '\0')
//                 {
//                     if(str_recup[i] == '\'')
//                     {
//                         str_recup = sup_cote(str_recup);
//                         break;
//                     }
//                     i++;
//                 }
//             }
//         }
//     }
//     return (str_recup);
// }

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
