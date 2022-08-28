/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convuint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:43:16 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/09 12:45:24 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_num_len(uint64_t nbr, int base)
{
	int				len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

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

static void	ft_utoa_buf(t_printf *pf, uint64_t n, int len, int base)
{
	int		i;

	i = len - 1;
	pf->buffer[pf->size + i] = '0';
	while (n > 0)
	{
		pf->buffer[pf->size + i] = (n % base) + '0';
		n /= base;
		i--;
	}
	pf->size += len;
}

static t_cinfo	ft_offload(t_conv *conv, uint64_t val, int base)
{
	t_cinfo	inf;

	inf.max = conv->prec;
	inf.len = ft_get_num_len(val, base);
	if (inf.len > inf.max)
		inf.max = inf.len;
	inf.min = inf.len;
	if (conv->min > inf.min)
		inf.min = conv->min;
	inf.total = inf.min;
	if (inf.max == inf.len && conv->flags[f_alt] && base == 8)
		inf.max++;
	if (inf.max > inf.min)
		inf.total = inf.max;
	return (inf);
}

int	ft_convuint(t_printf *pf, t_conv *conv, uint64_t val, int base)
{
	t_cinfo	inf;

	inf = ft_offload(conv, val, base);
	if (!ft_request(pf, inf.total))
		return (0);
	if (conv->flags[f_zpad] && !conv->prec)
		inf.min = 0;
	if (!conv->flags[f_nfield])
		ft_spacing(pf, inf.min - inf.max, ' ');
	if (conv->flags[f_zpad] && !conv->prec)
		ft_spacing(pf, inf.total - inf.len, '0');
	else
		ft_spacing(pf, inf.max - inf.len, '0');
	ft_utoa_buf(pf, val, inf.len, base);
	if (conv->flags[f_nfield])
		ft_spacing(pf, inf.min - inf.max, ' ');
	return (1);
}
