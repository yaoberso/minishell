/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:23:19 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/11 09:32:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (!(c >= 32 && c <= 126))
	{
		return (0);
	}
	return (1);
}

/*
#include <stdio.h>
int main(void)
{
	char *str = "Bonjour";
	printf("%i", ft_isprint(str));
	return (0);
}*/
