/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nas <nas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:59:02 by nadahman          #+#    #+#             */
/*   Updated: 2025/04/07 14:35:15 by nas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_builtin(t_cmd *cur_cmd, t_env *env, char *cmd_path)
{
	cmd_exec(cur_cmd, env);
	free(cmd_path);
}

static void	prepare_execution(t_cmd *cur_cmd, int fd[2], char ***args)
{
	if (cur_cmd->redirection && cur_cmd->cmd != NULL)
		exec_redir(cur_cmd);
	*args = get_args(cur_cmd);
	close_pipes(fd);
}

static void	execute_command(char *cmd_path, char **args, char **envp)
{
	execve(cmd_path, args, envp);
	// perror("execve");
	free(cmd_path);
	free_tab(args);
	exit(127);
}

void	exec_process(t_cmd *cur_cmd, int fd[2], t_env *env, char **envp)
{
	char	**args;
	char	*cmd_path;

	if (!cur_cmd || !cur_cmd->cmd)
		return ;
	if (!cur_cmd->env)
		cur_cmd->env = env;
	cmd_path = found_path(cur_cmd, env);
	if (is_cmd(cur_cmd->cmd) == 1)
	{
		handle_builtin(cur_cmd, env, cmd_path);
		return ;
	}
	prepare_execution(cur_cmd, fd, &args);
	if (!args)
	{
		perror("get_args");
		free(cmd_path);
		exit(1);
	}
	execute_command(cmd_path, args, envp);
}
