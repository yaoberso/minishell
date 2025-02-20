/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:21:05 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/11 09:31:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (!(c >= '0' && c <= '9'))
	{
		return (0);
	}
	return (1);
}

/*
#include <stdio.h>
int main(void)
{
	char *str = "salut 74200";
	printf("%i", ft_isdigit(str));
	return (0);
}*/