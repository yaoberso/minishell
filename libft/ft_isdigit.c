/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:28:03 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/02 11:02:24 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int i)
{
	if (i <= '9' && i >= '0')
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
