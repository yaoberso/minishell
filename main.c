/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:42:10 by nadahman          #+#    #+#             */
/*   Updated: 2025/04/20 16:07:33 by yann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	g_val_ret = 0;

void	reset_cmd(t_cmd *cmd)
{
	free_content_cmd(cmd);
	cmd->cmd = NULL;
	cmd->arg = NULL;
	cmd->redirection = NULL;
	cmd->next_cmd = NULL;
	cmd->prev_cmd = NULL;
	cmd->heredoc_fd = -1;
	cmd->save_stdin = -1;
}

void	execute_input(t_cmd *cmd, t_env *env_list, char **envp, char *input)
{
	if (cmd->cmd || cmd->arg || cmd->redirection || cmd->next_cmd)
		reset_cmd(cmd);
	parsing(input, cmd, env_list);
	if (cmd->if_error == 0)
	{
		cmd->env = env_list;
		exec_pipe(cmd, env_list, envp);
	}
	else
		cmd->if_error = 0;
}

void	loop_minishell(t_cmd *cmd, t_env *env_list, char **envp)
{
	char			*input;
	struct termios	term;
	char			*prompt;

	tcgetattr(STDIN_FILENO, &term);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	while (1)
	{
		config_signals();
		prompt = creat_prompt(env_list);
		input = readline(prompt);
		free(prompt);
		if (!check_exit_signal(input))
			break ;
		if (skip_if_empty_or_spaces(input))
			continue ;
		add_history(input);
		execute_input(cmd, env_list, envp, input);
		free(input);
		restore_signals();
	}
}

int	ms_status(int new_value)
{
	static int	status;

	if (new_value != -1)
		status = new_value;
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	t_env	*env_list;

	(void)argc;
	(void)argv;
	env_list = init_env(envp);
	cmd = init_cmd_struct(env_list);
	loop_minishell(cmd, env_list, envp);
	free_all(cmd, env_list);
	return (0);
}
