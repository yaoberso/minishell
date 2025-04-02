/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:35:26 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/01 14:29:35 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmd(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}

void	cmd_exec(t_cmd *cmd, t_env *env)
{
	if (cmd->cmd == NULL || cmd == NULL)
	{
		return ;
	}
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		ft_cd(cmd->arg, env);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd->arg);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		ft_env(env);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		ft_export(cmd->arg, &env);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		ft_unset(cmd->arg, &env);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
	{
		printf("exit\n");
		exit (1);
	}
}

int	cmd_in_pipe(char *cmd)  // les commandes qui doivent pas fonctionner dans un pipe
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	// else if (ft_strcmp(cmd, "export") == 0)
	// 	return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);	
}
