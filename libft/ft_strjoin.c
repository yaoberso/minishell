/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:03:23 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/08 12:52:51 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_strcpy_cust(char *dest, const char *src, int *i)
{
	int		j;

	j = 0;
	while (src[j] != '\0')
	{
		dest[*i] = src[j];
		(*i)++;
		j++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		len1;
	int		len2;
	int		i;

	if (s1 == NULL && s2 == NULL)
	{
		result = (char *)malloc(1);
		if (result == NULL)
			return (NULL);
		result[0] = '\0';
		return (result);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	if (s1 != NULL)
		ft_strcpy_cust(result, s1, &i);
	if (s2 != NULL)
		ft_strcpy_cust(result, s2, &i);
	result[i] = '\0';
	return (result);
}
/*
#include <stdio.h>

int main(void)
{
    char *result;

    char str1[] = "Hello, ";
    char str2[] = "World!";  
    result = ft_strjoin(str1, str2);
    printf("%s\n", result);
    
    free(result);
    return (0);
}
*/