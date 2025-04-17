/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:22:49 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/01 13:24:14 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int i)
{
	if (i >= 32 && i <= 126)
	{
		return (1);
	}
	i++;
	return (0);
}
/*
#include <stdio.h>
int main(void)
{
	char *str = "uygfwugf";
	printf("%i", ft_isalnum(str));
	return (0);
}*/
