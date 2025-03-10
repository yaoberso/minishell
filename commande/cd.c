/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:35:30 by yaoberso          #+#    #+#             */
/*   Updated: 2025/03/10 13:35:32 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_token *arg, t_env *env)
{
	char	cwd[1024];
	char	*home;
	char	*old_pwd;

	if (arg == NULL)
	{
		home = get_env_value(env, "HOME");
		if (home)
		{
			old_pwd = get_env_value(env, "PWD");
			if (old_pwd)
				set_env_value(env, "OLDPWD", old_pwd);
			if (chdir(home) == 0)
				set_env_value(env, "PWD", home);
			else
				perror("cd");
		}
		else
			printf("HOME not set\n");
	}
	else
	{
		if (chdir(arg->value) == 0)
		{
			if (getcwd(cwd, sizeof(cwd)))
				set_env_value(env, "PWD", cwd);
		}
		else
			perror("cd");
	}
}
