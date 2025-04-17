/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:10:29 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/08 13:30:02 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*s = (const unsigned char *)src;
	unsigned char		*d;

	d = (unsigned char *)dest;
	if (d == NULL && s == NULL)
		return (NULL);
	i = 0;
	if (d < s)
	{
		while (n--)
		{
			*d++ = *s++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
	}
	return (dest);
}
/*
#include <stdio.h>

int main(void)
{
    char src[] = "Overlap";
    char dest[20];

    ft_memmove(dest, src, 8);
    printf("ft_memmove result: %s\n", dest);

    ft_memmove(src + 3, src, 5);
    printf("ft_memmove overlapping result: %s\n", src);

    return (0);
}
*/