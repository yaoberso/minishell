/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:35:26 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/11 09:29:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	pos;

	pos = 0;
	while (pos < n)
	{
		((char *)s)[pos] = 0;
		pos++;
	}
}

/*
#include <stdio.h>

int main(void)
{
    char str[6] = "Hello";

    ft_bzero(str, 3);

    printf("Chaîne après ft_bzero : %s\n", str);

    return (0);
}
*/