/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:12:08 by nadahman          #+#    #+#             */
/*   Updated: 2024/10/11 09:30:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = count * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_bzero(ptr, total_size);
	return (ptr);
}

/*
int main(void)
{
    int *arr = (int *)ft_calloc(5, sizeof(int));

    if (!arr)
        return (1);

    printf("Premier élément du tableau après ft_calloc : %d\n", arr[0]);

    free(arr);
    return (0);
}
*/