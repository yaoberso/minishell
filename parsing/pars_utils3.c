/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:32:07 by nas               #+#    #+#             */
/*   Updated: 2025/04/01 12:15:33 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sup_cote(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			j++;
		i++;
	}
	new_str = malloc(sizeof(char) * (j + 1));
	if (!new_str)
		return (str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (free(str), new_str);
}

char	*sup_exp(char *str)
{
	char	*new_str;
	int		copy_chars;

	copy_chars = count_non_var_chars(str);
	new_str = malloc(sizeof(char) * (copy_chars + 1));
	if (!new_str)
		return (str);
	fill_new_str(str, new_str);
	free(str);
	return (new_str);
}

int	double_quote_with_simple_quote(char *str, int double_quote)
{
	int	i;

	i = 0;
	if (double_quote == 1)
	{
		while (str[i])
		{
			if (str[i] == '\'')
				return (1);
			i++;
		}
	}
	return (0);
}
