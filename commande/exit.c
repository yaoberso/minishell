/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yann <yann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:30:44 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/20 16:09:20 by yann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
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

static void	handle_exit_value(t_token *arg, int *ms_ex, int count)
{
	if (!is_numeric(arg->value))
	{
		printf("exit: %s: numeric argument required\n", arg->value);
		*ms_ex = 2;
	}
	else
	{
		*ms_ex = ft_atoi(arg->value);
		if (count > 1)
			printf("exit: too many arguments\n");
	}
}

void	process_exit_args(t_token *arg, int *ms_ex, int *count)
{
	t_token	*temp;

	*count = 0;
	if (arg == NULL)
	{
		*ms_ex = 0;
		return ;
	}
	temp = arg;
	while (temp != NULL)
	{
		(*count)++;
		temp = temp->next;
	}
	handle_exit_value(arg, ms_ex, *count);
}

void	ft_exit(t_cmd *cmd, t_env *env)
{
	int		ms_ex;
	int		count;
	t_token	*arg;

	arg = cmd->arg;
	printf("exit\n");
	process_exit_args(arg, &ms_ex, &count);
	if (count > 1 && is_numeric(arg->value))
	{
		handle_stdin_stdout(cmd);
		return ;
	}
	handle_stdin_stdout(cmd);
	free_cmd(cmd);
	free_env(env);
	exit(ms_ex);
}
