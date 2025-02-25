/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:16:13 by nas               #+#    #+#             */
/*   Updated: 2025/02/25 10:54:13 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_arguments(t_token *arg)
{
    while (arg != NULL)
    {
        printf("Argument: %s\n", arg->value);
        arg = arg->next;
    }
}

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}