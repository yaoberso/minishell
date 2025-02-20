/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:47:45 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/11 09:37:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s == NULL || f == NULL)
	{
		return ;
	}
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*
int main(void)
{
    char str[] = "Hello, World!";
    unsigned int i = 0;

    while (str[i] != '\0')
    {
        printf("Index %u: %c\n", i, str[i]);
        i++;
    }   
    return (0);
}
*/