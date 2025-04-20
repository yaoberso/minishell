/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:35:09 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/20 16:03:39 by yann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg(t_token *arg)
{
	t_token	*temp;
	int		arg_count;

	arg_count = 0;
	if (arg != NULL)
	{
		temp = arg;
		while (temp)
		{
			arg_count++;
			temp = temp->next;
		}
		if (arg_count > 0)
			return (1);
	}
	return (0);
}

void	ft_env(t_env *env, t_token *arg)
{
	t_env	*current;

	if (check_arg(arg))
	{
		printf("env: %s: No such file or directory\n", arg->value);
		ms_status(127);
		return ;
	}
	current = env;
	while (current)
	{
		printf("%s=\"%s\"\n", current->name, current->value);
		current = current->next;
	}
	ms_status(0);
}
