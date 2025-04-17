/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:19:53 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/09 13:47:53 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}
/*
#include <stdio.h>

int main(void)
{
    char *result;

    result = ft_strchr("Hello, World!", 'W');
    printf("%s\n", result);

    result = ft_strchr("Hello, World!", 'z');
    printf("%s\n", result ? result : "Not found");

    return (0);
}
*/