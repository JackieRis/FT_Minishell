/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:48:12 by aberneli          #+#    #+#             */
/*   Updated: 2022/02/24 14:39:31 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	ft_count_words(char const *str, char c)
{
	size_t	count;
	int		in_word;
	int		i;

	count = 0;
	in_word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		if (str[i] == c && in_word)
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*ft_get_next_word(char const *str, char c, int *i)
{
	char	*result;
	size_t	len;
	size_t	j;

	len = 0;
	while (str[len + *i] != '\0' && str[len + *i] != c)
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	j = 0;
	while (str[*i] != '\0' && str[*i] != c)
	{
		result[j] = str[*i];
		(*i)++;
		j++;
	}
	result[len] = '\0';
	while (str[*i] != '\0' && str[*i] == c)
		(*i)++;
	return (result);
}

void	*split_free(char **spl)
{
	size_t	i;

	i = 0;
	if (!spl)
		return (NULL);
	while (spl[i])
	{
		free(spl[i]);
		i++;
	}
	free(spl);
	return (NULL);
}

char	**split(char const *str, char c)
{
	char	**spl;
	size_t	words;
	size_t	w;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] == c)
		i++;
	words = ft_count_words(str, c);
	spl = (char **)malloc((words + 1) * sizeof(char *));
	if (!spl)
		return (NULL);
	spl[words] = NULL;
	w = 0;
	while (w < words)
	{
		spl[w] = ft_get_next_word(str, c, &i);
		if (!spl[w])
			return (split_free(spl));
		w++;
	}
	return (spl);
}
