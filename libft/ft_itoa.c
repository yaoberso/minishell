/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:57:12 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/09 10:10:40 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_size(long nb)
{
	size_t		size;

	size = 0;
	if (nb <= 0)
	{
		size = 1;
		nb = -nb;
	}
	while (nb != 0)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	size_t	size;
	long	nb;
	char	*str;

	nb = (long) n;
	size = count_size(nb);
	str = (char *) malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
	{
		str[0] = '0';
	}
	while (nb != 0)
	{
		str[--size] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);
}
/*
#include <stdio.h>
int main()
{
    char    *str;
    int     num;

    num= -8753;
    str = ft_itoa(num);
    printf("%s", str);
    free(str);
    return (0);
}
*/
