/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:34:41 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/15 13:18:19 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[1024];

	g_val_ret = 0;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		g_val_ret = 1;
		exit(1);
	}
	printf("%s\n", cwd);
}
