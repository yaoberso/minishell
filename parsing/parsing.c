/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:27:05 by nas               #+#    #+#             */
/*   Updated: 2025/04/01 10:06:00 by yann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *replace_exit_status(char *str, int start)
{
	char	*val_ret_str;
	char	*result;
	int		len_before;
	int		len_after;

	val_ret_str = ft_itoa(val_ret);
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

char *extract_var_name(char *str, int start, int *end)
{
	*end = start + 1;
	while (str[*end] && (ft_isalnum(str[*end]) || str[*end] == '_'))
		(*end)++;
	return ((*end - start - 1 > 0) ? 
		ft_substr(str, start + 1, *end - start - 1) : NULL);
}

char *replace_var_in_str(char *str, int start, char *var_value, int end)
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

char *expand_var_at_position(char *str, int *pos, t_env *env)
{
	int		start;
	int		end;
	char	*var_name;
	char	*var_value;
	char	*result;

	start = *pos;
	if (str[start + 1] == '?')
	{
		result = replace_exit_status(str, start);
		*pos = start + ft_strlen(ft_itoa(val_ret));
		return (result);
	}
	var_name = extract_var_name(str, start, &end);
	if (!var_name)
		return (ft_strdup(str));
	var_value = get_env_value(env, var_name);
	free(var_name);
	result = replace_var_in_str(str, start, var_value ? var_value : "", end);
	*pos = start + ft_strlen(var_value ? var_value : "");
	return (result);
}

char update_quote_state(char current_char, char quote_state)
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

char *expand_variables(char *str, t_env *env)
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
		if (result[i] == '$' && quote_state != '\'')
		{
			expanded = expand_var_at_position(result, &i, env);
			if (!expanded)
				return (NULL);
			free(result);
			result = expanded;
			continue;
		}
		i++;
	}
	return (result);
}

char *initialize_process_quotes(char *str, int *j)
{
	char	*result;

	*j = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (str);
	return (result);
}

void handle_quote_chars(char current_char, char *quote_state, 
						char *result, int *j)
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

char *process_quotes(char *str)
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

void find_token_bounds(char *str, int *start, int *end, int *index)
{
	int		i;
	char	current_quote;

	i = *index;
	current_quote = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
	{
		*start = i;
		*end = i;
		*index = i;
		return ;
	}
	*start = i;
	while (str[i] && ((!ft_isspace(str[i]) || current_quote) && 
		  ((str[i] != '<' && str[i] != '>' && str[i] != '|') || current_quote)))
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

char *process_token(char *str_recup, t_env *env)
{
	char	*result;

	if (!str_recup)
		return (NULL);
	checkif2(str_recup, '"');
	checkif2(str_recup, '\'');
	result = expand_variables(str_recup, env);
	free(str_recup);
	if (!result)
		return (NULL);
	result = process_quotes(result);
	return (result);
}

char *recup_token(char *str, int *index, t_env *env)
{
	int		start;
	int		end;
	char	*str_recup;

	find_token_bounds(str, &start, &end, index);
	if (end <= start)
		return (NULL);
	str_recup = ft_substr(str, start, end - start);
	return (process_token(str_recup, env));
}

void initialize_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	cmd->cmd = NULL;
	cmd->arg = NULL;
	cmd->redirection = NULL;
	cmd->next_cmd = NULL;
	config_signals_exec();
}

void process_single_token(char *token, t_cmd *cmd)
{
	if (token)
	{
		if (cmd->cmd == NULL)
			cmd->cmd = token;
		else
			add_token(&cmd->arg, new_token(token));
	}
}

int process_parsing_char(char *str, int *i, t_cmd *cmd, t_env *env)
{
	t_redirection	*new_redir;
	t_cmd			*next_cmd;
	char			*token;

	if (str[*i] == '<' || str[*i] == '>')
	{
		new_redir = found_redirection(str, i, env);
		if (new_redir)
			add_redirection(cmd, new_redir);
	}
	else if (str[*i] == '|')
	{
		next_cmd = found_next_cmd(str, i, env);
		if (next_cmd)
		{
			add_next_cmd(cmd, next_cmd);
			next_cmd->prev_cmd = cmd;
		}
		return (1);
	}
	else
	{
		token = recup_token(str, i, env);
		process_single_token(token, cmd);
	}
	return (0);
}

void parsing(char *str, t_cmd *cmd, t_env *env)
{
	int	i;

	i = 0;
	if (str == NULL || cmd == NULL)
		return ;
	initialize_cmd(cmd);
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		if (process_parsing_char(str, &i, cmd, env))
			break ;
	}
	restore_signals();
}
