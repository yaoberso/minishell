/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:34:21 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/01 12:44:37 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, const char *name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

void	set_env_value(t_env *env, const char *name, const char *new_value)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			free(env->value);
			env->value = ft_strdup(new_value);
			return ;
		}
		env = env->next;
	}
}

void	print_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		printf("declare -x %s=\"%s\"\n", current->name, current->value);
		current = current->next;
	}
}

void	update_or_add_env(t_env **env, char *var_name, char *var_value)
{
	t_env	*current;

	current = *env;
	while (current && ft_strcmp(current->name, var_name) != 0)
		current = current->next;
	if (current)
	{
		free(current->value);
		current->value = var_value;
	}
	else
		add_env_variable(env, var_name, var_value);
}
