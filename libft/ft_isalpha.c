/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:21:46 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/01 12:27:47 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int i)
{
	if ((i >= 'a' && i <= 'z')
		|| (i >= 'A' && i <= 'Z'))
	{
		return (1);
	}
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
