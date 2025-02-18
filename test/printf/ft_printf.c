/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadahman <nadahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:02:22 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/17 13:43:20 by nadahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	found_conv(char conv, va_list args)
{
	if (conv == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (conv == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (conv == 'p')
		return (ft_putpointer(va_arg(args, void *)));
	else if (conv == 'd')
		return (ft_putnbr(va_arg(args, int)));
	else if (conv == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (conv == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int)));
	else if (conv == 'x')
		return (ft_putnbr_hex(va_arg(args, unsigned int), 'x'));
	else if (conv == 'X')
		return (ft_putnbr_hex(va_arg(args, unsigned int), 'X'));
	else if (conv == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		nbr_char;
	va_list	args;

	va_start (args, format);
	i = 0;
	nbr_char = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			nbr_char += found_conv(format[i], args);
		}
		else
		{
			nbr_char += ft_putchar(format[i]);
		}
		i++;
	}
	va_end(args);
	return (nbr_char);
}
/*int main() 
{
	ft_printf("%p", "ok");
    return (0);
}*/