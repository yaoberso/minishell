/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:09:07 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/08 11:41:21 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int i)
{
	if (i >= 'A' && i <= 'Z')
	{
		i = i + 32;
	}
	return (i);
}
/*
#include <stdio.h>

int main(void)
{
    char c = 'A';
    
    printf("'%c'\n", c, ft_tolower(c));
    
    return (0);
}
*/