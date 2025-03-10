/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:35:23 by yaoberso          #+#    #+#             */
/*   Updated: 2025/03/10 13:35:25 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_token *current)
{
	int		newline;
	t_token	*arg;
	int		i;

	newline = 1;
	arg = current;
	if (!arg)
	{
		write(1, "\n", 1);
		return ;
	}
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
