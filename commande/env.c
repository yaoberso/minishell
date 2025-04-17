/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:35:09 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/17 13:15:08 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *arg)
{
	t_env	*current;

	current = arg;
	while (current)
	{
		printf("%s=\"%s\"\n", current->name, current->value);
		current = current->next;
	}
	ms_status(0);
}
