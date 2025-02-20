/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:22:35 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/11 09:36:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}
/*
int main(void)
{
    char *result;

    result = ft_strchr("Hello, World!", 'W');
    printf("%s\n", result);

    result = ft_strchr("Hello, World!", 'z');
    printf("%s\n", result ? result : "Not found");

    return (0);
}
*/