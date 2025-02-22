/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:00:08 by nas               #+#    #+#             */
/*   Updated: 2025/02/22 10:12:40 by nas              ###   ########.fr       */
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

// la fonction qui va extraire toutes les commandes des arguments
char *recup_token(char *str, int *index)
{
    int i;
    int start;
    int end;
    char c;
    char *str_recup;

    i = *index;
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    if (str[i] == '"' || str[i] == '\'')
    {
        c = str[i];
        i++;
        start = i;
        while (str[i] && str[i] != c)
            i++;

        end = i;
        i++;
    }
    else
    {
        start = i;
        while (str[i] && (str[i] != ' ' && str[i] != '\t'))
            i++;

        end = i;
    }
    if (end > start)
    {
        *index = i;
        str_recup = malloc(sizeof(char) * (end - start + 1));
        if (str_recup == NULL)
            return (NULL);
        ft_strlcpy(str_recup, str + start, end - start + 1);
        return str_recup;
    }
    return NULL;
}

void print_arguments(t_token *arg)
{
    while (arg != NULL)
    {
        printf("Argument: %s\n", arg->value);
        arg = arg->next;
    }
}
