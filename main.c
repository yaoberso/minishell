/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:42:10 by nadahman          #+#    #+#             */
/*   Updated: 2025/04/09 13:30:58 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	val_ret = 0;

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	struct termios	term;
	t_cmd			*cmd;
	t_env			*env_list;
	char			*prompt;

	(void)argc;
	(void)argv;
	env_list = init_env(envp);
	cmd = malloc(sizeof(t_cmd));
	tcgetattr(STDIN_FILENO, &term);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// config_signals();
	cmd->cmd = NULL;
	cmd->arg = NULL;
	cmd->redirection = NULL;
	cmd->next_cmd = NULL;
	cmd->prev_cmd = NULL;
	cmd->heredoc_fd = -1;
	cmd->save_stdin = -1;
	cmd->std = malloc(sizeof(t_std));
	cmd->std->save_instd = -1;
	cmd->std->save_outstd = -1;
	cmd->std->original_stdin = -1;
	cmd->env = env_list;
	while (1)
	{
		config_signals();
		prompt = creat_prompt(env_list);
		input = readline(prompt);
		free(prompt);
		if (!input)
		{
			free(cmd->std);
			free(cmd);
			free_env(env_list);
			printf("exit\n");
			break ;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		if (input && is_only_spaces(input) == 1)
		{
			free(input);
			continue ;
		}
		if (*input)
			add_history(input);
		if (cmd->cmd || cmd->arg || cmd->redirection || cmd->next_cmd)
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
		parsing(input, cmd, env_list);
		if (val_ret == 1)
		{
			val_ret = 0;
		}
		else
		{
			cmd->env = env_list;
			exec_pipe(cmd, env_list, envp);
			restore_signals();
		}
		free(input);
		restore_signals();
	}
	return (0);
}

// #include "minishell.h"

// int val_ret = 0;
// t_signal g_signal = {0, 0};

// int	main(int argc, char **argv, char **envp)
// {
// 	char			*input;
// 	struct termios	term;
// 	t_cmd			*cmd;
// 	t_env			*env_list;
// 	char			*prompt;

// 	(void)argc;
// 	(void)argv;
// 	env_list = init_env(envp);
// 	tcgetattr(STDIN_FILENO, &term);
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);

// 	while (1)
// 	{
// 		config_signals();
// 		prompt = creat_prompt(env_list);
// 		input = readline(prompt);
// 		free(prompt);

// 		if (!input)
// 		{
// 			printf("exit\n");
// 			free_env(env_list);
// 			break ;
// 		}

// 		if (input[0] == '\0' || is_only_spaces(input))
// 		{
// 			free(input);
// 			continue ;
// 		}

// 		add_history(input);

// 		cmd = malloc(sizeof(t_cmd));
// 		if (!cmd)
// 		{
// 			perror("malloc");
// 			free(input);
// 			continue ;
// 		}
// 		ft_memset(cmd, 0, sizeof(t_cmd));
// 		cmd->heredoc_fd = -1;
// 		cmd->save_stdin = -1;
// 		cmd->env = env_list;

// 		parsing(input, cmd, env_list);

// 		if (val_ret != 1)
// 		{
// 			exec_pipe(cmd, env_list, envp);
// 			printf("JE SUIS DANS LE PARENT\n");
// 		}
// 		else
// 			val_ret = 0;

// 		free_cmd(cmd);
// 		free(input);
// 		restore_signals();
// 	}
// 	return (0);
// }
