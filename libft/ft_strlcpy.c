/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:16:50 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/04 10:41:06 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;

	i = 0;
	if (dstsize == 0)
	{
		return (ft_strlen(src));
	}
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}
/*
#include <stdio.h>

int main(void)
{
    const char *src = "Bonjour, le monde!";
    printf(%s\n", ft_strlcpy(dest, src, 20));

    return (0);
}
*/