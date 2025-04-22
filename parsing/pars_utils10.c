/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils10.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:13:30 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/22 12:00:14 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_non_var_chars(char *str)
{
	int	i;
	int	copy_chars;

	i = 0;
	copy_chars = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != ' ')
		{
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '\t'
				&& str[i] != '\'' && str[i] != '"')
				i++;
		}
		else
		{
			copy_chars++;
			i++;
		}
	}
	return (copy_chars);
}

void	fill_new_str(char *str, char *new_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != ' ')
		{
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '\t'
				&& str[i] != '\'' && str[i] != '"')
				i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
}

char	*replace_variable(char *str, int start, char *var_value, int end)
{
	if (var_value)
		return (replace_var_in_str(str, start, var_value, end));
	return (replace_var_in_str(str, start, "", end));
}

int	skip_spaces(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

void	processe_token(char *str, int *i, t_cmd *cmd, t_env *env)
{
	char	*token;

	token = recup_token(str, i, env);
	process_single_token(token, cmd);
}
