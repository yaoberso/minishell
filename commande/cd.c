/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:35:30 by yaoberso          #+#    #+#             */
/*   Updated: 2025/03/16 13:24:55 by yann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cdwitharg(t_env *env, t_token *arg)
{
	char	cwd[1024];
	char	*old_pwd;

	if (!arg || !arg->value)
	{
		printf("cd: missing argument\n");
		return ;
	}
	old_pwd = get_env_value(env, "PWD");
	if (old_pwd)
		set_env_value(env, "OLDPWD", old_pwd);
	if (chdir(arg->value) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)))
			set_env_value(env, "PWD", cwd);
	}
	else
		perror("cd");
}

void	ft_cd(t_token *arg, t_env *env)
{
	char	cwd[1024];
	char	*home;
	char	*old_pwd;

	if (!arg || !arg->value)
	{
		home = get_env_value(env, "HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			return ;
		}
		old_pwd = get_env_value(env, "PWD");
		if (old_pwd)
			set_env_value(env, "OLDPWD", old_pwd);
		if (chdir(home) == 0)
		{
			if (getcwd(cwd, sizeof(cwd)))
				set_env_value(env, "PWD", cwd);
		}
		else
			perror("cd");
	}
	else
		ft_cdwitharg(env, arg);
	val_ret = 0;
}
