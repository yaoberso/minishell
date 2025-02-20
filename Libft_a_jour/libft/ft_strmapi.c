/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:44:58 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/08 13:47:12 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	size_t				len;
	char				*new_str;

	if (s == NULL)
	{
		return (NULL);
	}
	len = ft_strlen(s);
	new_str = malloc(len + 1);
	i = 0;
	if (new_str == NULL)
	{
		return (NULL);
	}
	while (i < len)
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[len] = '\0';
	return (new_str);
}
/*
#include <stdio.h>
int main()
{
	char *str = "Salut toi";
	char *result = ft_strmapi(str, to_lower);
	if (result != NULL)
	{
	printf("%s", result);
	free(result);
	}
	return (0);
}
*/