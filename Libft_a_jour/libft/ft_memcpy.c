/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:43:37 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/11 09:34:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)src;

	d = (unsigned char *)dest;
	i = 0;
	if (d == NULL && s == NULL)
	{
		return (NULL);
	}
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/*
int main(void)
{
    char src[] = "Hello, World!";
    char dest[20];

    ft_memcpy(dest, src, 13);
    printf("ft_memcpy result: %s\n", dest);

    return (0);
}
*/