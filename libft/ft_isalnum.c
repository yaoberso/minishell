/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:11:26 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/04 10:19:28 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int i)
{
	if ((ft_isalpha(i) || ft_isdigit(i)))
	{
		return (1);
	}
	return (0);
}
/*
#include <stdio.h>
int main(void)
{
	char *str = "uygfwugf 82328";
	printf("%i", ft_isalnum(str));
	return (0);
}*/
