/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convuint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:43:16 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/09 13:12:30 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_spacing(t_printf *pf, int len, char c)
{
	int		i;

	if (len < 1)
		return ;
	i = 0;
	while (i < len)
	{
		pf->buffer[pf->size] = c;
		pf->size++;
		i++;
	}
}

static t_cinfo	ft_offload(t_conv *conv, char *str)
{
	t_cinfo	inf;

	inf.max = conv->prec;
	inf.len = ft_strlen(str);
	if (conv->type == 'c' && inf.len == 0)
		inf.len = 1;
	inf.min = conv->min;
	if (inf.len > inf.max && conv->hasprec)
		inf.len = inf.max;
	inf.total = inf.len;
	if (inf.min > inf.total)
		inf.total = inf.min;
	return (inf);
}

int	ft_convstr(t_printf *pf, t_conv *conv, char *str)
{
	t_cinfo	inf;
	size_t	off;

	off = 0;
	inf = ft_offload(conv, str);
	if (!ft_request(pf, inf.total))
		return (0);
	if (conv->flags[f_zpad])
		inf.min = 0;
	if (!conv->flags[f_nfield])
		ft_spacing(pf, inf.min - inf.len, ' ');
	if (conv->flags[f_zpad])
		ft_spacing(pf, inf.total - inf.len, '0');
	while (off < inf.len)
	{
		pf->buffer[pf->size] = str[off];
		pf->size++;
		off++;
	}
	if (conv->flags[f_nfield])
		ft_spacing(pf, inf.min - inf.len, ' ');
	return (1);
}
