/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:01:40 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/15 13:12:52 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkif2(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			count++;
		}
		i++;
	}
	if (count % 2 != 0)
	{
		printf("synthax error : quote\n");
		return (0);
	}
	return (1);
}

char	*replace_exit_status(char *str, int start)
{
	char	*val_ret_str;
	char	*result;
	int		len_before;
	int		len_after;

	val_ret_str = ft_itoa(g_val_ret);
	if (!val_ret_str)
		return (ft_strdup(str));
	len_before = start;
	len_after = ft_strlen(str + start + 2);
	result = malloc(len_before + ft_strlen(val_ret_str) + len_after + 1);
	if (!result)
	{
		free(val_ret_str);
		return (ft_strdup(str));
	}
	ft_memcpy(result, str, len_before);
	strcpy(result + len_before, val_ret_str);
	strcpy(result + len_before + ft_strlen(val_ret_str), str + start + 2);
	free(val_ret_str);
	return (result);
}

char	*extract_var_name(char *str, int start, int *end)
{
	*end = start + 1;
	while (str[*end] && (ft_isalnum(str[*end]) || str[*end] == '_'))
		(*end)++;
	if (*end - start - 1 > 0)
		return (ft_substr(str, start + 1, *end - start - 1));
	return (NULL);
}

char	*replace_var_in_str(char *str, int start, char *var_value, int end)
{
	int		len_before;
	int		len_after;
	char	*result;

	len_before = start;
	len_after = ft_strlen(str + end);
	result = malloc(len_before + ft_strlen(var_value) + len_after + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, str, len_before);
	strcpy(result + len_before, var_value);
	strcpy(result + len_before + ft_strlen(var_value), str + end);
	return (result);
}

char	*expand_var_at_position(char *str, int *pos, t_env *env)
{
	int		start;
	int		end;
	char	*var_name;
	char	*var_value;
	char	*result;
	char	*val_str;

	start = *pos;
	if (str[start + 1] == '?')
	{
		result = replace_exit_status(str, start);
		val_str = ft_itoa(g_val_ret);
		*pos = start + ft_strlen(val_str);
		free(val_str);
		return (result);
	}
	var_name = extract_var_name(str, start, &end);
	if (!var_name)
		return (ft_strdup(str));
	var_value = get_env_value(env, var_name);
	free(var_name);
	result = replace_variable(str, start, var_value, end);
	if (var_value)
		*pos = start + ft_strlen(var_value);
	else
		*pos = start;
	return (result);
}
