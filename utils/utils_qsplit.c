/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_qsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 10:53:10 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/22 11:41:14 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	qsplit_cw(char const *str)
{
	size_t	count;
	int		in_word;
	int		i;
	char	mode;

	count = 0;
	in_word = 0;
	i = 0;
	mode = 0;
	while (str[i])
	{
		if (mode == 0 && (str[i] == '\'' || str[i] == '"'))
			mode = str[i];
		else if (str[i] == mode)
			mode = 0;
		if (!contains(WSPACE, str[i]) && !in_word)
		{
			in_word = 1;
			count++;
		}
		if (contains(WSPACE, str[i]) && in_word && mode == 0)
			in_word = 0;
		i++;
	}
	return (count);
}

static size_t	qsplit_wlen(char const *str, size_t *i)
{
	size_t	j;
	char	mode;

	j = 0;
	mode = 0;
	while (str[*i + j])
	{
		if (mode == 0 && contains(WSPACE, str[*i + j]))
			return (j);
		if (mode == 0 && (str[*i + j] == '\'' || str[*i + j] == '"'))
			mode = str[*i + j];
		else if (str[*i + j] == mode)
			mode = 0;
		j++;
	}
	return (j);
}

static char	*qsplit_nextword(char const *str, size_t *i)
{
	char	*result;
	size_t	len;
	size_t	j;

	len = qsplit_wlen(str, i);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	j = 0;
	while (j < len)
	{
		result[j] = str[*i];
		(*i)++;
		j++;
	}
	while (str[*i] != '\0' && contains(WSPACE, str[*i]))
		(*i)++;
	return (result);
}

char	**qsplit(char const *str)
{
	char	**spl;
	size_t	words;
	size_t	w;
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && contains(WSPACE, str[i]))
		i++;
	words = qsplit_cw(str);
	spl = (char **)malloc((words + 1) * sizeof(char *));
	if (!spl)
		return (NULL);
	spl[words] = NULL;
	w = 0;
	while (w < words)
	{
		spl[w] = qsplit_nextword(str, &i);
		if (!spl[w])
			return (split_free(spl));
		w++;
	}
	return (spl);
}
