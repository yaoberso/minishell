/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:55:59 by nadahman          #+#    #+#             */
/*   Updated: 2025/04/15 12:32:39 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_absolute_path(t_cmd *cmd, char **paths)
{
	if (cmd->cmd[0] == '/' || cmd->cmd[0] == '.')
	{
		if (access(cmd->cmd, F_OK | X_OK) == 0)
		{
			free_tab(paths);
			return (ft_strdup(cmd->cmd));
		}
		free_tab(paths);
		return (NULL);
	}
	return ((char *)-1);
}

char	*search_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*found_path(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**paths;
	char	*result;

	path = get_env_value(env, "PATH");
	if (path == NULL || cmd->cmd == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	result = check_absolute_path(cmd, paths);
	if (result != (char *)-1)
		return (result);
	result = search_in_paths(paths, cmd->cmd);
	free_tab(paths);
	return (result);
}
