/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:34:58 by yaoberso          #+#    #+#             */
/*   Updated: 2025/03/16 13:26:41 by yann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_arg_name(char *arg)
{
	int		i;
	int		len;
	char	*name;

	i = 0;
	len = 0;
	while (arg[len] != '=' && arg[len] != '\0')
		len++;
	if (len == 0)
		return (NULL);
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (i < len)
	{
		name[i] = arg[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*extract_arg_value(char *arg)
{
	int		i;
	int		j;
	int		len;
	char	*value;

	i = 0;
	while (arg[i] != '=' && arg[i] != '\0')
		i++;
	if (arg[i] == '=')
		i++;
	len = 0;
	while (arg[i + len] != '\0')
		len++;
	if (len >= 2 && arg[i] == '"' && arg[i + len - 1] == '"')
	{
		i++;
		len -= 2;
	}
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	j = 0;
	while (j < len)
	{
		value[j] = arg[i + j];
		j++;
	}
	value[j] = '\0';
	return (value);
}

void	add_env_variable(t_env **env, char *var_name, char *var_value)
{
	t_env	*new_var;
	t_env	*temp;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return ;
	new_var->name = var_name;
	new_var->value = var_value;
	new_var->next = NULL;
	if (*env == NULL)
	{
		*env = new_var;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = new_var;
}

void	ft_export(t_token *arg, t_env **env)
{
	t_env	*current;
	t_token	*current_arg;
	char	*var_name;
	char	*var_value;

	if (!arg)
	{
		current = *env;
		while (current)
		{
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
			current = current->next;
		}
		return ;
	}
	current_arg = arg;
	while (current_arg)
	{
		var_name = extract_arg_name(current_arg->value);
		var_value = extract_arg_value(current_arg->value);
		if (!var_name)
		{
			printf("export: `%s': not a valid identifier\n",
				current_arg->value);
			current_arg = current_arg->next;
			continue ;
		}
		current = *env;
		while (current)
		{
			if (ft_strcmp(current->name, var_name) == 0)
			{
				free(current->value);
				current->value = var_value;
				break ;
			}
			current = current->next;
		}
		if (!current)
		{
			add_env_variable(env, var_name, var_value);
		}
		current_arg = current_arg->next;
	}
	val_ret = 0;
}
