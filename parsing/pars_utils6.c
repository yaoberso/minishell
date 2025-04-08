/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:01:46 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/08 13:15:00 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper function for recup_token to find token boundaries
void	find_token_bounds(char *str, int *start, int *end, int *index)
{
	int		i;
	char	current_quote;

	current_quote = 0;
	i = *index;
	i = skip_spaces(str, i);
	if (!str[i])
	{
		*start = i;
		*end = i;
		*index = i;
		return ;
	}
	*start = i;
	while (str[i] && ((!ft_isspace(str[i]) || current_quote) && ((str[i] != '<'
					&& str[i] != '>' && str[i] != '|') || current_quote)))
	{
		if (!current_quote && (str[i] == '\'' || str[i] == '"'))
			current_quote = str[i];
		else if (current_quote && str[i] == current_quote)
			current_quote = 0;
		i++;
	}
	*end = i;
	*index = i;
}

// Process token after extraction
char	*process_token(char *str_recup, t_env *env)
{
	char	*result;

	if (!str_recup)
		return (NULL);
	if (checkif2(str_recup, '"') == 0 || checkif2(str_recup, '\'') == 0)
	{
		free(str_recup);
		return (NULL);
	}
	result = expand_variables(str_recup, env);
	free(str_recup);
	if (!result)
		return (NULL);
	result = process_quotes(result);
	return (result);
}
