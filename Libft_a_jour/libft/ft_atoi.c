/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:37:21 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/09 11:37:23 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calcul(const char *str, int *i, int s)
{
	int	r;

	r = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		r = r * 10 + (str[*i] - 48);
		(*i)++;
	}
	return (r * s);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		s;
	int		count;

	i = 0;
	s = 1;
	count = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			s = s * -1;
		}
		if (count == 1)
		{
			return (0);
		}
		i++;
		count++;
	}
	return (calcul(str, &i, s));
}
/*
#include <stdio.h>
int main(void)
{
  char *str = " -79547";
  printf("%i", ft_atoi(str));
	return(0);
}
*/