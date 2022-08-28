/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:13:22 by aberneli          #+#    #+#             */
/*   Updated: 2022/02/19 16:09:35 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_extend_buffer(t_printf *pf)
{
	char	*tmp;

	pf->capacity *= 2;
	tmp = malloc(pf->capacity);
	if (!tmp)
	{
		free(pf->buffer);
		return (0);
	}
	ft_memcpy(tmp, pf->buffer, pf->size);
	free(pf->buffer);
	pf->buffer = tmp;
	return (1);
}

int	ft_request(t_printf *pf, size_t n)
{
	while ((n + 16) > pf->capacity - pf->size)
	{
		if (!ft_extend_buffer(pf))
			return (0);
	}
	return (1);
}

int	ft_append(t_printf *pf, const char *data, size_t n)
{
	if (!ft_request(pf, n))
		return (0);
	ft_memcpy(&pf->buffer[pf->size], data, n);
	pf->size += n;
	return (1);
}

int	ft_has(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
