/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:14:29 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/15 13:15:15 by yaoberso         ###   ########.fr       */
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
