/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:34:31 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/17 13:15:48 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_unset(t_env *current, t_env *prev, t_env **env)
{
	if (!current)
		return ;
	if (prev)
		prev->next = current->next;
	else
		*env = current->next;
	free(current->name);
	free(current->value);
	free(current);
}

void	ft_unset(t_token *arg, t_env **env)
{
	t_token	*current_arg;
	t_env	*current;
	t_env	*prev;

	current_arg = arg;
	ms_status(0);
	while (current_arg)
	{
		current = *env;
		prev = NULL;
		while (current)
		{
			if (ft_strcmp(current->name, current_arg->value) == 0)
			{
				ft_free_unset(current, prev, env);
				break ;
			}
			prev = current;
			current = current->next;
		}
		current_arg = current_arg->next;
	}
}
