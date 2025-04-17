/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:34:41 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/17 13:15:29 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[1024];

	ms_status(0);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		ms_status(1);
		exit(1);
	}
	printf("%s\n", cwd);
}
