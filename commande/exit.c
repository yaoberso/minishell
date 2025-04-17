/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:30:44 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/17 13:58:39 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i <= '9' && i >= '0')
		{
			i++;
		}
		else
		{
			return (1);
		}
	}
	return (0);
}

void	handle_stdin_stdout(t_cmd *cmd)
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
}

void	process_exit_args(t_token *arg, int *ms_ex, int *count)
{
	if (arg == NULL)
		*ms_ex = 0;
	else
	{
		if (check_if_alpha(arg->value) == 1)
		{
			printf("exit: %s: numeric argument required\n", arg->value);
			*ms_ex = 2;
		}
		else
		{
			*ms_ex = ft_atoi(arg->value);
			while (arg != NULL)
			{
				(*count)++;
				arg = arg->next;
			}
			if (*count > 1)
				printf("exit: too many arguments\n");
		}
	}
}

void	ft_exit(t_cmd *cmd, t_env *env)
{
	int		ms_ex;
	int		count;
	t_token	*arg;

	count = 0;
	arg = cmd->arg;
	printf("exit\n");
	process_exit_args(arg, &ms_ex, &count);
	handle_stdin_stdout(cmd);
	free_cmd(cmd);
	free_env(env);
	exit(ms_ex);
}
