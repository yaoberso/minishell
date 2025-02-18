/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:43:19 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/17 13:41:32 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

int	ft_putnbr(long nb)
{
	int	count;

	count = 0;
	if (nb == LONG_MIN)
	{
		count += ft_putstr("-9223372036854775808");
		return (count);
	}
	if (nb < 0)
	{
		count += ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		count += ft_putnbr(nb / 10);
	}
	count += ft_putchar(nb % 10 + '0');
	return (count);
}

int	ft_putnbr_unsigned(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb >= 10)
	{
		count += ft_putnbr_unsigned(nb / 10);
	}
	count += ft_putchar(nb % 10 + '0');
	return (count);
}

int	ft_putnbr_hex(unsigned long nb, char format)
{
	char	*base;
	int		count;

	base = NULL;
	count = 0;
	if (format == 'x')
	{
		base = "0123456789abcdef";
	}
	else if (format == 'X')
	{
		base = "0123456789ABCDEF";
	}
	if (base != NULL)
	{		
		if (nb >= 16)
		{
			count += ft_putnbr_hex(nb / 16, format);
		}
	}
	count += ft_putchar(base[nb % 16]);
	return (count);
}

int	ft_putpointer(void *ptr)
{
	unsigned long	adress;
	int				count;

	count = 0;
	ft_putstr("0x");
	count = count + 2;
	if (ptr == NULL)
	{
		count += ft_putstr("0");
		return (count);
	}
	adress = (unsigned long)ptr;
	count += ft_putnbr_hex(adress, 'x');
	return (count);
}
