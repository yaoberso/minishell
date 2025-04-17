/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:29:10 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/04 10:40:07 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < dstsize && dst[i] != '\0')
	{
		i++;
	}
	if (i >= dstsize)
	{
		return (i + ft_strlen(src));
	}
	while (src[j] != '\0' && (i + j + 1) < dstsize)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
/*
#include <stdio.h>

int main(void)
{
    char dest[20] = "Hello, ";
    char src[] = "World!";

    ft_strlcat(dest, src, 20);
    printf("Chaîne résultante : %s\n", dest);

    return (0);
}
*/