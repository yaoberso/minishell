/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:34:21 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/24 11:49:43 by yaoberso         ###   ########.fr       */
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

void	update_or_add_env(t_env **env, char *var_name, char *var_value)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->name, var_name) == 0)
		{
			free(var_name);
			if (current->value)
				free(current->value);
			current->value = var_value;
			return ;
		}
		current = current->next;
	}
	add_env_variable(env, var_name, var_value);
}

int	print_env(t_env *env_list, int flag)
{
	t_env	**env_array;
	int		env_count;

	if (!env_list)
		return (0);
	env_count = count_env_nodes(env_list);
	env_array = create_env_array(env_list, env_count);
	if (!env_array)
		return (1);
	sort_env_array(env_array, env_count);
	print_sorted_env(env_array, env_count, flag);
	free(env_array);
	return (0);
}
