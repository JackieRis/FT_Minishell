/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:29:30 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/09 13:16:47 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	conv_sint(t_printf *pf, t_conv *conv, t_tfmt value)
{
	return (ft_convsint(pf, conv, value.dec));
}

static int	conv_uint(t_printf *pf, t_conv *conv, t_tfmt value)
{
	if (conv->type == 'u')
		return (ft_convuint(pf, conv, (uint64_t)value.udec, 10));
	if (conv->type == 'o')
		return (ft_convuint(pf, conv, (uint64_t)value.udec, 8));
	return (0);
}

static int	conv_hex(t_printf *pf, t_conv *conv, t_tfmt value)
{
	if (conv->type == 'p')
		conv->flags[f_alt] = 1;
	if (conv->type == 'X')
		conv->basestr = BASE16_BIG;
	if (conv->type != 'p' && conv->flags[f_alt] && value.udec == 0)
		conv->flags[f_alt] = 0;
	if (conv->type == 'p')
		return (ft_convxint(pf, conv, (uint64_t)value.ptr));
	return (ft_convxint(pf, conv, (uint64_t)value.udec));
}

static int	conv_str(t_printf *pf, t_conv *conv, t_tfmt value)
{
	char	tmp[2];

	tmp[0] = '%';
	tmp[1] = '\0';
	if (conv->type == 'c' || conv->type == '!')
		tmp[0] = value.c;
	if (conv->type == 's')
	{
		if (value.str == NULL)
			value.str = NULLSTR;
		return (ft_convstr(pf, conv, value.str));
	}
	else
		return (ft_convstr(pf, conv, tmp));
	return (0);
}

int	ft_converter(t_printf *pf, t_conv *conv, t_tfmt value)
{
	conv->basestr = BASE16_SMALL;
	if (conv->type == 'd' || conv->type == 'i')
		return (conv_sint(pf, conv, value));
	if (conv->type == 'u' || conv->type == 'o' || conv->type == 'b')
		return (conv_uint(pf, conv, value));
	if (conv->type == 'x' || conv->type == 'X' || conv->type == 'p')
		return (conv_hex(pf, conv, value));
	if (conv->type == 's' || conv->type == 'c' || conv->type == '%')
		return (conv_str(pf, conv, value));
	if (conv->type == '!')
		return (conv_str(pf, conv, value));
	return (0);
}
