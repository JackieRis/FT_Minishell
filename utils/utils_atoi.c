/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:55:54 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/26 14:39:02 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int	ft_atoi(const char *s)
{
	int	i;
	int	r;
	int	n;

	i = 0;
	n = 1;
	if (s[i] == '-')
	{
		n = -1;
		i++;
	}
	r = 0;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		r = r * 10 + (s[i] - '0');
		i++;
	}
	return (r * n);
}

int64_t	ft_atoi_error(const char *s, int *valid)
{
	size_t					i;
	unsigned long long int	r;
	int						n;

	i = 0;
	n = 1;
	if (s[i] == '-')
	{
		n = -1;
		i++;
	}
	r = 0;
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
	{
		r = r * 10 + (s[i] - '0');
		i++;
	}
	if ((r > 9223372036854775807UL && n == 1) \
		|| ((n == -1) && r > 9223372036854775808UL) \
		|| i > 19 + (s[0] == '-'))
		(*valid) = -1;
	r = r * n;
	return ((long long int)r);
}
