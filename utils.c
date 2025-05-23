/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:14:29 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/16 10:25:58 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*creat_prompt(t_env *env)
{
	char	*pwd;
	char	*prompt;
	size_t	len;

	pwd = get_env_value(env, "PWD");
	if (!pwd)
	{
		return (NULL);
	}
	len = strlen(pwd) + 3;
	prompt = (char *)malloc(len * sizeof(char));
	if (!prompt)
	{
		return (NULL);
	}
	strcpy(prompt, pwd);
	strcat(prompt, "$ ");
	return (prompt);
}

int	is_only_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]) && str[i] != '"' && str[i] != '\'')
			return (0);
		i++;
	}
	return (1);
}

t_cmd	*init_cmd_struct(t_env *env_list)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->arg = NULL;
	cmd->redirection = NULL;
	cmd->next_cmd = NULL;
	cmd->prev_cmd = NULL;
	cmd->heredoc_fd = -1;
	cmd->save_stdin = -1;
	cmd->std = malloc(sizeof(t_std));
	if (!cmd->std)
		return (cmd);
	cmd->std->save_instd = -1;
	cmd->std->save_outstd = -1;
	cmd->std->original_stdin = -1;
	cmd->if_error = 0;
	cmd->env = env_list;
	return (cmd);
}

int	check_exit_signal(char *input)
{
	if (!input)
	{
		printf("exit\n");
		return (0);
	}
	return (1);
}
