/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:05:37 by aberneli          #+#    #+#             */
/*   Updated: 2022/02/19 16:37:48 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>

# include "utils.h"

# define CONVERT_STR "cspdiuxXo%"
# define FLAGS_STR "-0+ #"
# define BASE16_SMALL "0123456789abcdef"
# define BASE16_BIG "0123456789ABCDEF"
# define NULLSTR "(null)"

typedef enum e_flags
{
	f_alt = 0,
	f_zpad = 1,
	f_nfield = 2,
	f_blank = 3,
	f_plus = 4
}				t_flags;

typedef union s_tfmt
{
	void			*ptr;
	char			*str;
	int				dec;
	unsigned int	udec;
	char			c;
}					t_tfmt;

typedef struct s_cinfo
{
	size_t		len;
	size_t		min;
	size_t		max;
	size_t		total;
	int			sign;
}				t_cinfo;

typedef struct s_conv
{
	t_flags		flags[5];
	char		*basestr;
	size_t		min;
	size_t		prec;
	int			type;
	char		err;
	char		hasprec;
}				t_conv;

typedef struct s_printf
{
	char		*buffer;
	size_t		size;
	size_t		fmtoff;
	size_t		capacity;
}				t_printf;

// ft_printf.c
int		ft_printf(int fd, int code, char *fmt, ...);

// ft_tools.c
int		ft_extend_buffer(t_printf *pf);
int		ft_request(t_printf *pf, size_t n);
int		ft_append(t_printf *pf, const char *data, size_t n);
int		ft_has(const char *s, char c);

// ft_getters.c
void	get_flags(const char *fmt, t_printf *pf, t_conv *conv);
void	get_mwidth(const char *fmt, t_printf *pf, t_conv *conv);
void	get_prec(const char *fmt, t_printf *pf, t_conv *conv);
void	get_type(const char *fmt, t_printf *pf, t_conv *conv);

// ft_converter.c
int		ft_converter(t_printf *pf, t_conv *conv, t_tfmt value);

// ft_convsint.c
int		ft_convsint(t_printf *pf, t_conv *conv, int val);

// ft_convuint.c
int		ft_convuint(t_printf *pf, t_conv *conv, uint64_t val, int base);

// ft_convxint.c
int		ft_convxint(t_printf *pf, t_conv *conv, uint64_t val);

// ft_convstr.c
int		ft_convstr(t_printf *pf, t_conv *conv, char *str);

#endif
