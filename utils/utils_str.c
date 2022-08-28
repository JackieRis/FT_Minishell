/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:39:26 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/22 16:43:52 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_str	str_new(void)
{
	t_str	str;

	str.cap = 16;
	str.len = 0;
	str.s = malloc(str.cap);
	if (!str.s)
		return (str);
	str.s[str.len] = '\0';
	return (str);
}

int	str_request(t_str *str, size_t addsize)
{
	char	*tmp;

	if (!str->s)
		return (0);
	if (str->len + addsize < str->cap - 1)
		return (1);
	while (str->len + addsize >= str->cap)
		str->cap *= 2;
	tmp = malloc(str->cap);
	if (!tmp)
	{
		free(str->s);
		str->s = NULL;
		return (0);
	}
	ft_memcpy(tmp, str->s, str->len);
	free(str->s);
	str->s = tmp;
	return (1);
}

void	str_add(t_str *str, char c)
{
	if (!str_request(str, 2))
		return ;
	str->s[str->len++] = c;
	str->s[str->len] = '\0';
}

void	str_append(t_str *str, char *s)
{
	int	i;

	if (!s)
		return ;
	if (!str_request(str, ft_strlen(s) + 1))
		return ;
	i = 0;
	while (s[i])
	{
		str->s[str->len] = s[i];
		str->len++;
		i++;
	}
	str->s[str->len] = '\0';
}
