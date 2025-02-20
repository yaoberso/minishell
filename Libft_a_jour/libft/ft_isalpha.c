/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:22:32 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/07 13:30:35 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (!((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')))
	{
		return (0);
	}
	return (1);
}
/*
#include <stdio.h>
int main (void)
{
	printf("%d", ft_isalpha('5'));
			return (0);
}
*/