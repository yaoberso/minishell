/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:51:59 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/08 11:41:27 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int i)
{
	if (i >= 'a' && i <= 'z')
	{
		i = i - 32;
	}
	return (i);
}
/*
#include <stdio.h>

int main(void)
{
    char c = 'A';
    
    printf("'%c'\n", c, ft_toupper(c));
    
    return (0);
}
*/