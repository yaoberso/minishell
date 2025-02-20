/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaoberso <yaoberso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:38:55 by yaoberso          #+#    #+#             */
/*   Updated: 2024/10/09 13:38:57 by yaoberso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s != '\0')
	{
		if (*s == c)
		{
			in_word = 0;
		}
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*extraire(const char *s, char c, size_t *start)
{
	size_t	end;
	char	*word;

	end = *start;
	while (s[end] && s[end] != c)
	{
		end++;
	}
	word = (char *)malloc(end - *start + 1);
	if (word != NULL)
	{
		ft_strlcpy(word, s + *start, end - *start + 1);
	}
	*start = end + 1;
	return (word);
}

static char	**ft_free(char **result, int i)
{
	while (i > 0)
	{
		free(result[--i]);
	}
	free(result);
	result = NULL;
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**result;
	size_t	start;
	int		i;	

	start = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (i < word_count)
	{
		while (s[start] == c)
			start++;
		result[i] = extraire(s, c, &start);
		if (result[i] == NULL)
			return (ft_free(result, i));
		i++;
	}
	result[i] = NULL;
	return (result);
}
/*
#include <stdio.h>
int main(void)
{
    char *str = "Bonjour tout le monde";
    char delim = ' ';
    char **result;

    result = ft_split(str, delim);

    if (result == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        return (1);
    }

    for (int i = 0; result[i] != NULL; i++)
    {
        printf("Sous-chaîne %d : %s\n", i, result[i]);
        free(result[i]);
    }

    free(result);
    return (0);
}
*/
