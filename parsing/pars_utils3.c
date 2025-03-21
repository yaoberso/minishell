/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:32:07 by nas               #+#    #+#             */
/*   Updated: 2025/03/21 13:58:03 by yann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *sup_cote(char *str)
{
    int i = 0;
    int j = 0;
    char *new_str;

    while (str[i])
    {
        if (str[i] != '\'' && str[i] != '"')
            j++;
        i++;
    }
    
    new_str = malloc(sizeof(char) * (j + 1));
    if (!new_str)
        return (str);
    
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] != '\'' && str[i] != '"')
            new_str[j++] = str[i];
        i++;
    }
    new_str[j] = '\0';
    
    free(str);
    return (new_str);
}

char *sup_exp(char *str)
{
    int i = 0;
    int j = 0;
    int copy_chars = 0;
    char *new_str;

    while (str[i])
    {
        if (str[i] == '$')
        {
            i++;
            while (str[i] && str[i] != ' ' && str[i] != '\t')
                i++;
        }
        else
        {
            copy_chars++;
            i++;
        }
    }
    
    new_str = malloc(sizeof(char) * (copy_chars + 1));
    if (!new_str)
        return (str);
    
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
            i++;
            while (str[i] && str[i] != ' ' && str[i] != '\t' && 
                str[i] != '\'' && str[i] != '"') 
                i++;
        }
        else
        {
            new_str[j++] = str[i++];
        }
    }
    new_str[j] = '\0';
    
    free(str);
    return (new_str);
}

int only_simple_quote(char *str, int double_quote)
{
    int i = 0;
    
	if (double_quote == 0)
	{
    	while (str[i])
    	{
        	if (str[i] == '\'')
            	return 1;
        	i++;
    	}
	}
    return 0;
}

