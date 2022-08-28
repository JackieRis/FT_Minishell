/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convsint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:39:13 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/22 11:32:55 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_num_len(int nbr)
{
	int				len;
	unsigned int	check;

	len = 0;
	if (nbr == 0)
		return (1);
	check = nbr;
	if (nbr < 0)
		check = -nbr;
	while (check > 0)
	{
		check /= 10;
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

static void	ft_utoa_buf(t_printf *pf, unsigned int n, int len)
{
	int		i;

	i = len - 1;
	pf->buffer[pf->size + i] = '0';
	while (n > 0)
	{
		pf->buffer[pf->size + i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	pf->size += len;
}

static void	ft_write_sint(t_printf *pf, t_conv *conv, t_cinfo inf, int val)
{
	if (inf.sign)
	{
		pf->buffer[pf->size] = ' ';
		if (conv->flags[f_plus])
			pf->buffer[pf->size] = '+';
		if (val < 0)
			pf->buffer[pf->size] = '-';
		pf->size++;
	}
	if (conv->flags[f_zpad] && !conv->prec)
		inf.min = 0;
	if (!conv->flags[f_nfield])
		ft_spacing(pf, inf.min - inf.max, ' ');
	if (conv->flags[f_zpad] && !conv->prec)
		ft_spacing(pf, inf.total - inf.len - inf.sign, '0');
	else
		ft_spacing(pf, inf.max - inf.len - inf.sign, '0');
	if (val < 0)
		ft_utoa_buf(pf, -val, inf.len);
	else
		ft_utoa_buf(pf, val, inf.len);
}

int	ft_convsint(t_printf *pf, t_conv *conv, int val)
{
	t_cinfo	inf;

	inf.sign = (conv->flags[f_blank] || conv->flags[f_plus] || val < 0);
	inf.max = conv->prec + inf.sign;
	inf.len = ft_get_num_len(val);
	if (inf.len + inf.sign > inf.max)
		inf.max = inf.len + inf.sign;
	inf.min = inf.len + inf.sign;
	if (conv->min > inf.min)
		inf.min = conv->min;
	inf.total = inf.min;
	if (inf.max > inf.min)
		inf.total = inf.max;
	if (!ft_request(pf, inf.total))
		return (0);
	ft_write_sint(pf, conv, inf, val);
	if (conv->flags[f_nfield])
		ft_spacing(pf, inf.min - inf.max, ' ');
	return (1);
}
