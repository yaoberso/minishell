/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:35:23 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/15 13:12:52 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_echo(t_token *arg, int newline)
{
	while (arg != NULL)
	{
		write(1, arg->value, ft_strlen(arg->value));
		if (arg->next)
			write(1, " ", 1);
		arg = arg->next;
	}
	if (newline)
		write(1, "\n", 1);
}

int	check_arg_null(t_token *arg)
{
	if (!arg)
	{
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

void	ft_echo(t_token *current)
{
	int		newline;
	t_token	*arg;
	int		i;

	newline = 1;
	arg = current;
	if (check_arg_null(arg) == 1)
		return ;
	while (arg && ft_strncmp(arg->value, "-n", 2) == 0)
	{
		i = 2;
		while (arg->value[i] == 'n')
			i++;
		if (arg->value[i] == '\0')
		{
			newline = 0;
			arg = arg->next;
		}
		else
			break ;
	}
	ft_print_echo(arg, newline);
	g_val_ret = 0;
}
