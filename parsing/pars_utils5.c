/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:01:43 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/07 10:55:07 by yann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	update_quote_state(char current_char, char quote_state)
{
	if (current_char == '\'')
	{
		if (quote_state == 0)
			return ('\'');
		else if (quote_state == '\'')
			return (0);
	}
	else if (current_char == '"')
	{
		if (quote_state == 0)
			return ('"');
		else if (quote_state == '"')
			return (0);
	}
	return (quote_state);
}

// Main expand_variables function
char	*expand_variables(char *str, t_env *env)
{
	int		i;
	char	quote_state;
	char	*result;
	char	*expanded;

	i = 0;
	quote_state = 0;
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	while (result[i])
	{
		quote_state = update_quote_state(result[i], quote_state);
		if (result[i] == '$' && quote_state != '\'' && result[i + 1] != '\0')
		{
			if (result[i + 1] == '?')
			{
				expanded = replace_exit_status(result, i);
				if (!expanded)
					return (NULL);
				free(result);
				result = expanded;
				i += 2;
				continue ;
			}
			else if (result[i + 1] == '$')
			{
				i += 2;
				continue ;
			}
			expanded = extract_var_name(result, i, &i);
			if (!expanded)
				return (NULL);
			result = replace_var_in_str(result, i, expanded, i);
			free(expanded);
			continue ;
		}
		else if (result[i] == '\\' && quote_state != '\'' && result[i + 1])
		{
			expanded = expand_var_at_position(result, &i, env);
			if (!expanded)
				return (NULL);
			free(result);
			result = expanded;
			continue ;
		}
		i++;
	}
	return (result);
}

// process_quotes split into initialize and main functions
char	*initialize_process_quotes(char *str, int *j)
{
	char	*result;

	*j = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (str);
	return (result);
}

void	handle_quote_chars(char current_char, char *quote_state, char *result,
		int *j)
{
	if (current_char == '\'')
	{
		if (*quote_state == 0)
			*quote_state = '\'';
		else if (*quote_state == '\'')
			*quote_state = 0;
		else if (*quote_state == '"')
			result[(*j)++] = current_char;
	}
	else if (current_char == '"')
	{
		if (*quote_state == 0)
			*quote_state = '"';
		else if (*quote_state == '"')
			*quote_state = 0;
		else if (*quote_state == '\'')
			result[(*j)++] = current_char;
	}
	else
		result[(*j)++] = current_char;
}

char	*process_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;
	char	quote_state;

	i = 0;
	quote_state = 0;
	result = initialize_process_quotes(str, &j);
	if (result == str)
		return (str);
	while (str[i])
	{
		handle_quote_chars(str[i], &quote_state, result, &j);
		i++;
	}
	result[j] = '\0';
	free(str);
	return (result);
}
