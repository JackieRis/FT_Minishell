/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convxint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:12:46 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/09 14:19:40 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_num_len(uint64_t nbr)
{
	int				len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr /= 16;
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

static void	ft_utoa_buf(t_printf *pf, const char *b, uint64_t n, int len)
{
	int		i;

	i = len - 1;
	pf->buffer[pf->size + i] = '0';
	while (n > 0)
	{
		pf->buffer[pf->size + i] = b[n % 16];
		n /= 16;
		i--;
	}
	pf->size += len;
}

static void	ft_suffix(t_printf *pf, t_conv *conv, t_cinfo *inf)
{
	if (conv->flags[f_zpad] && !conv->prec)
		inf->min = 0;
	if (!conv->flags[f_nfield])
		ft_spacing(pf, inf->min - inf->max - (conv->flags[f_alt] * 2), ' ');
	if (conv->flags[f_alt])
	{
		pf->buffer[pf->size] = '0';
		pf->buffer[pf->size + 1] = 'x';
		if (conv->type == 'X')
			pf->buffer[pf->size + 1] = 'X';
		pf->size += 2;
	}
	if (conv->flags[f_zpad] && !conv->prec)
		ft_spacing(pf, inf->total - inf->len - (conv->flags[f_alt] * 2), '0');
	else
		ft_spacing(pf, inf->max - inf->len, '0');
}

int	ft_convxint(t_printf *pf, t_conv *conv, uint64_t val)
{
	t_cinfo	inf;

	inf.max = conv->prec;
	inf.len = ft_get_num_len(val);
	if (inf.len > inf.max)
		inf.max = inf.len;
	inf.min = inf.len;
	if (conv->min > inf.min)
		inf.min = conv->min;
	inf.total = inf.min;
	if (inf.max > inf.min)
		inf.total = inf.max;
	if (!ft_request(pf, inf.total))
		return (0);
	ft_suffix(pf, conv, &inf);
	ft_utoa_buf(pf, conv->basestr, val, inf.len);
	if (conv->flags[f_nfield])
		ft_spacing(pf, inf.min - inf.max - (conv->flags[f_alt] * 2), ' ');
	return (1);
}
