/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:50:05 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/11 09:39:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*mem;

	start = 0;
	end = ft_strlen(s1);
	if (s1 == NULL)
		return (NULL);
	while (s1[start] && is_in(s1[start], set))
	{
		start++;
	}
	while (end > start && is_in(s1[end - 1], set))
	{
		end--;
	}
	mem = (char *)malloc(end - start + 1);
	if (mem == NULL)
		return (NULL);
	ft_strlcpy(mem, s1 + start, end - start + 1);
	mem[end - start] = '\0';
	return (mem);
}
/*
int main(void)
{
    char *s1 = "   Bonjour, le monde!   ";
    char *set = " ";
    char *result;

    result = ft_strtrim(s1, set);
    printf("Chaîne après trim : '%s'\n", result);

    free(result);
    return (0);
}
*/