/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 09:56:18 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/11 13:12:59 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last_occ;

	i = 0;
	last_occ = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			last_occ = (char *)&s[i];
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)&s[i]);
	}
	return (last_occ);
}
/*
#include <stdio.h>

int main(void)
{
    char *str = "Hello World!";
    char ch = 'o';

    char *result = ft_strrchr(str, ch);
    printf("Dernière occ '%c': %s\n", ch, ft_strrchr(str, ch));

    return (0);
}
*/