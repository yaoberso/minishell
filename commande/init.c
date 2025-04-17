/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:34:48 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/01 12:44:13 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_init(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

static t_env	*create_env_node(char *env_entry, char *equal)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = strndup(env_entry, equal - env_entry);
	new->value = strdup(equal + 1);
	if (!new->name || !new->value)
	{
		free(new->name);
		free(new->value);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

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
		if (equal)
		{
			new = create_env_node(envp[i], equal);
			if (!new)
			{
				free_env_init(head);
				return (NULL);
			}
			new->next = head;
			head = new;
		}
		i++;
	}
	return (head);
}
