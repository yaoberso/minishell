/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:38:08 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/09 11:38:08 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *) haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
	j = 0;
		while (haystack[i + j] != '\0' && haystack[i + j]
			== needle[j] && i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *) haystack + i);
			i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int main(void)
{
    char *haystack = "Bonjour tout le monde!";
    char *needle = "tout";
    size_t len = 20;

    char *result = ft_strnstr(haystack, needle, len);
    printf("%s\n", result ? result : "Sous-chaîne non trouvée");

    return (0);
}
*/