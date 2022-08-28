/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:55:22 by aberneli          #+#    #+#             */
/*   Updated: 2022/02/19 16:25:07 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

void	get_flags(const char *fmt, t_printf *pf, t_conv *conv)
{
	while (ft_has(FLAGS_STR, fmt[pf->fmtoff]))
	{
		if (fmt[pf->fmtoff] == '#')
			conv->flags[f_alt] = 1;
		if (fmt[pf->fmtoff] == '0')
			conv->flags[f_zpad] = 1;
		if (fmt[pf->fmtoff] == '-')
			conv->flags[f_nfield] = 1;
		if (fmt[pf->fmtoff] == ' ')
			conv->flags[f_blank] = 1;
		if (fmt[pf->fmtoff] == '+')
			conv->flags[f_plus] = 1;
		pf->fmtoff++;
	}
	if (conv->flags[f_plus])
		conv->flags[f_blank] = 0;
	if (conv->flags[f_nfield])
		conv->flags[f_zpad] = 0;
}

void	get_mwidth(const char *fmt, t_printf *pf, t_conv *conv)
{
	size_t	pos;

	pos = 0;
	if (!ft_isdigit(fmt[pf->fmtoff]))
		return ;
	while (ft_isdigit(fmt[pf->fmtoff + pos]))
		pos++;
	conv->min = ft_atoi(&fmt[pf->fmtoff]);
	pf->fmtoff += pos;
}

void	get_prec(const char *fmt, t_printf *pf, t_conv *conv)
{
	size_t	pos;

	if (fmt[pf->fmtoff] != '.')
		return ;
	conv->hasprec = 1;
	pos = 1;
	while (ft_isdigit(fmt[pf->fmtoff + pos]))
		pos++;
	conv->prec = ft_atoi(&fmt[pf->fmtoff + 1]);
	pf->fmtoff += pos;
}

void	get_type(const char *fmt, t_printf *pf, t_conv *conv)
{
	if (!ft_has(CONVERT_STR, fmt[pf->fmtoff]))
	{
		conv->err = fmt[pf->fmtoff];
		conv->type = '!';
	}
	else
		conv->type = fmt[pf->fmtoff];
	if (fmt[pf->fmtoff])
		pf->fmtoff++;
}
