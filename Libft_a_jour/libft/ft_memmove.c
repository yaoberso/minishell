/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:54:58 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/11 09:34:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t					i;
	unsigned char			*d;
	const unsigned char		*s = (const unsigned char *)src;

	d = (unsigned char *)dest;
	i = 0;
	if (d == NULL && s == NULL)
		return (NULL);
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