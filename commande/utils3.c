/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:56:12 by yaoberso          #+#    #+#             */
/*   Updated: 2025/04/24 12:07:18 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_and_free(char *var_name, char *var_value, char *value)
{
	printf("minishell: export: `%s': not a valid identifier\n", value);
	if (var_name)
		free(var_name);
	if (var_value)
		free(var_value);
}
