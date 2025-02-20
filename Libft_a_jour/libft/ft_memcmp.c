/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:29:20 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/11 09:33:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ptr1 = (const unsigned char *)s1;
	const unsigned char	*ptr2 = (const unsigned char *)s2;

	i = 0;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
		{
			return (ptr1[i] - ptr2[i]);
		}
		i++;
	}
	return (0);
}

/*
int main(void)
{
    char str1[] = "Hello";
    char str2[] = "Hellp";
    int result;

    result = ft_memcmp(str1, str2, 5);
    printf("ft_memcmp result: %d\n", result);

    return (0);
}
*/