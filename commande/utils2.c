/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:46:53 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/24 11:50:52 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_varname(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	count_env_nodes(t_env *env_list)
{
	t_env	*current;
	int		count;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_env	**create_env_array(t_env *env_list, int env_count)
{
	t_env	**env_array;
	t_env	*current;
	int		i;

	env_array = ft_calloc(env_count, sizeof(t_env *));
	if (!env_array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		env_array[i++] = current;
		current = current->next;
	}
	return (env_array);
}

void	sort_env_array(t_env **env_array, int env_count)
{
	t_env	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < env_count - 1)
	{
		j = 0;
		while (j < env_count - i - 1)
		{
			if (ft_strcmp(env_array[j]->name, env_array[j + 1]->name) > 0)
			{
				temp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_sorted_env(t_env **env_array, int env_count, int flag)
{
	int	i;

	i = 0;
	while (i < env_count)
	{
		if (flag == 1)
		{
			if (env_array[i]->value)
				printf("declare -x %s=\"%s\"\n", env_array[i]->name,
					env_array[i]->value);
			else
				printf("declare -x %s\n", env_array[i]->name);
		}
		else
		{
			if (env_array[i]->value)
				printf("%s=%s\n", env_array[i]->name, env_array[i]->value);
		}
		i++;
	}
}
