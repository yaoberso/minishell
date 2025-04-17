/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:26:43 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/09 11:04:53 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;
	size_t		len_s;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
	{
		str = ((char *)malloc(1));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (len > len_s - start)
		len = len_s - start;
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>

int main(void)
{
    char *s = "Bonjour, le monde!";
    unsigned int start = 8;
    size_t len = 6;
    char *result;

    result = ft_substr(s, start, len);
    printf("Sous-chaîne extraite : '%s'\n", result);

    free(result);
    return (0);
}
*/