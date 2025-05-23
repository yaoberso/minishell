/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:35:26 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/16 10:41:35 by yaoberso         ###   ########.fr       */
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

void	handle_exit(t_cmd *cmd, t_env *env)
{
	if (cmd->std->original_stdin >= 0)
	{
		dup2(cmd->std->original_stdin, STDIN_FILENO);
		close(cmd->std->original_stdin);
		cmd->std->original_stdin = -1;
	}
	if (cmd->std->save_instd >= 0)
	{
		dup2(cmd->std->save_instd, STDIN_FILENO);
		close(cmd->std->save_instd);
		cmd->std->save_instd = -1;
	}
	if (cmd->std->save_outstd >= 0)
	{
		dup2(cmd->std->save_outstd, STDOUT_FILENO);
		close(cmd->std->save_outstd);
		cmd->std->save_outstd = -1;
	}
	free_cmd(cmd);
	free_env(env);
	printf("exit\n");
	exit(1);
}

void	cmd_exec(t_cmd *cmd, t_env *env)
{
	if (cmd == NULL || cmd->cmd == NULL)
		return ;
	if (ft_strcmp(cmd->cmd, "cd") == 0)
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
		handle_exit(cmd, env);
}

int	cmd_in_pipe(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}
