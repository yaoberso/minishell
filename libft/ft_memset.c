/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:35:39 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/04 10:38:13 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s2;
	size_t			i;

	i = 0;
	s2 = (unsigned char *)s;
	while (i < n)
	{
		s2[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>

int main(void)
{
    char str[20] = "Hello, World!";

    ft_memset(str, 'A', 5);
    printf("ft_memset result: %s\n", str);

    return (0);
}
*/