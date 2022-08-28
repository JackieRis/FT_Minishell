/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 00:47:07 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/25 18:24:46 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	contains(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	scontains(const char *s, const char *c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (c[j])
		{
			if (s[i] == c[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_num(char c)
{
	return (c >= 0 && c <= 9);
}

int	valid_name(const char *s, char c)
{
	size_t	i;

	i = 0;
	if ((s[0] >= '0' && s[0] <= '9') || contains(WSPACE, s[0]) || !s[0])
		return (0);
	while (s[i] && s[i] != c)
	{
		if (!contains(VALID_NAME_STR, s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valid_numstr(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
