/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:38:15 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/09 11:38:15 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			return (((char *)&s[i]));
		}
		i--;
	}
	return (NULL);
}
/*
int main(void)
{
    char *str = "Hello World!";
    char ch = 'o';

    char *result = ft_strrchr(str, ch);
    printf("Dernière occurrence de '%c': %s\n", ch, result ? result : "Non trouvé");

    return (0);
}
*/