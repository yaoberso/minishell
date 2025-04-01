/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:16:13 by nas               #+#    #+#             */
/*   Updated: 2025/04/01 12:02:49 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arguments(t_token *arg)
{
	while (arg != NULL)
	{
		printf("Argument: %s\n", arg->value);
		arg = arg->next;
	}
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

// pour creer un nouveau token en fonction de ce qu'on recupere
t_token	*new_token(char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->value = ft_strdup(str);
	token->next = NULL;
	return (token);
}

// pour ajouter un token a la fin de la liste
void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

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
void	add_redirection(t_cmd *cmd, t_redirection *new_redir)
{
	t_redirection	*tmp;

	if (cmd == NULL || new_redir == NULL)
		return ;
	if (cmd->redirection == NULL)
	{
		cmd->redirection = new_redir;
		return ;
	}
	else
	{
		tmp = cmd->redirection;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
}
