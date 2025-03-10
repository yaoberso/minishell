/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:34:48 by yaoberso          #+#    #+#             */
/*   Updated: 2025/03/10 13:34:50 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*new;
	char	*equal;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		equal = strchr(envp[i], '=');
		if (!equal)
		{
			i++;
			continue ;
		}
		new = malloc(sizeof(t_env));
		if (!new)
		{
			free_env(head);
			return (NULL);
		}
		new->name = strndup(envp[i], equal - envp[i]);
		new->value = strdup(equal + 1);
		if (!new->name || !new->value)
		{
			free(new->name);
			free(new->value);
			free(new);
			free_env(head);
			return (NULL);
		}
		new->next = head;
		head = new;
		i++;
	}
	return (head);
}
