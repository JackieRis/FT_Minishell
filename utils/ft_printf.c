/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:32:51 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/22 11:32:46 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	ft_get_conv(char *fmt, t_printf *pf, t_conv *conv)
{
	size_t	pos;
	char	*nextconv;

	ft_memset(conv, 0, sizeof(t_conv));
	nextconv = ft_strchr(&fmt[pf->fmtoff], '%');
	if (!nextconv)
	{
		ft_append(pf, &fmt[pf->fmtoff], ft_strlen(&fmt[pf->fmtoff]));
		return (0);
	}
	pos = (size_t)(nextconv - &fmt[pf->fmtoff]);
	if (!ft_append(pf, &fmt[pf->fmtoff], pos))
		return (0);
	pf->fmtoff += pos + 1;
	get_flags(fmt, pf, conv);
	get_mwidth(fmt, pf, conv);
	get_prec(fmt, pf, conv);
	get_type(fmt, pf, conv);
	return (conv->type);
}

static int	ft_parse_fmt(char *fmt, t_printf *pf, va_list lst)
{
	t_conv	conv;
	t_tfmt	value;

	while (ft_get_conv(fmt, pf, &conv))
	{
		if (conv.type == 'd' || conv.type == 'i')
			value.dec = va_arg(lst, int);
		if (conv.type == 'u' || conv.type == 'o')
			value.udec = va_arg(lst, unsigned int);
		if (conv.type == 'x' || conv.type == 'X')
			value.ptr = (void *)va_arg(lst, size_t);
		if (conv.type == 'p')
			value.ptr = va_arg(lst, void *);
		if (conv.type == 's')
			value.str = va_arg(lst, char *);
		if (conv.type == 'c')
			value.c = (char)va_arg(lst, int);
		if (conv.type == '%')
			value.c = '%';
		if (conv.type == '!')
			value.c = conv.err;
		ft_converter(pf, &conv, value);
	}
	return (1);
}

static void	ft_init_printf(t_printf *pf)
{
	pf->capacity = 32;
	pf->size = 0;
	pf->fmtoff = 0;
	pf->buffer = malloc(pf->capacity);
}

int	ft_printf(int fd, int code, char *fmt, ...)
{
	t_printf	pf;
	va_list		lst;

	if (!fmt)
		return (-1);
	ft_init_printf(&pf);
	if (!pf.buffer)
		return (-1);
	va_start(lst, fmt);
	if (!ft_parse_fmt(fmt, &pf, lst))
	{
		free(pf.buffer);
		va_end(lst);
		return (-1);
	}
	va_end(lst);
	pf.size = write(fd, pf.buffer, pf.size);
	free(pf.buffer);
	return (code);
}
