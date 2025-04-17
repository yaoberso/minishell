/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:12:04 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/04 10:23:43 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == ((unsigned char)c))
		{
			return ((void *)(s + i));
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int main(void)
{
    char str[] = "Hello World";
    char *result = (char *)ft_memchr(str, 'W', 11);

    if (result)
        printf("Caractère trouvé : %s\n", result);
    else
        printf("Caractère non trouvé\n");

    return (0);
}
*/