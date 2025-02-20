/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:41:00 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/09 14:14:41 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int static	calc(int s, int *i, const char *str)
{
	int		r;

	r = 0;
	while (str[*i] <= '9' && str[*i] >= '0')
	{
		r = r * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (r * s);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		r;
	int		s;
	int		count;

	count = 0;
	i = 0;
	r = 0;
	s = 1;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			s *= -1;
		}
		if (count > 0)
		{
			return (0);
		}
		i++;
		count++;
	}
	return (calc(s, &i, str));
}
/*
#include <stdio.h>

int main(void)
{
    char *str = "0";
    printf("%i", ft_atoi(str));
    return (0);
}*/
