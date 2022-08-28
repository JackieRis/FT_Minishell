/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:15:21 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/02/11 14:23:49 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_buf_write(int fd, const char *s, size_t buf)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	while (len - i >= buf)
	{
		write(fd, &s[i], buf);
		i += buf;
	}
	write(fd, &s[i], len - i);
}
