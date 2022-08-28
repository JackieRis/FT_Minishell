/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 21:57:01 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/25 16:30:10 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <unistd.h>

# include <env.h>

# include "ft_printf.h"

# define VALID_NAME_STR "_abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
# define IDENTIFIER_STR "_abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$\"'"
# define IDENTIFIER_QSTR "_abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$\"' \t\n\r\v\f"
# define WSPACE " \t\n\r\v\f"

typedef struct s_str
{
	char		*s;
	size_t		cap;
	size_t		len;
}				t_str;

// utils_str.c
t_str	str_new(void);
int		str_request(t_str *str, size_t addsize);
void	str_add(t_str *str, char c);
void	str_append(t_str *str, char *s);

// utils_str_expand.c
char	*expand_str(char *s, t_env *e);

// utils_write.c
void	ft_buf_write(int fd, const char *s, size_t buf);

// utils_len.c
size_t	ft_strlen_secure(const char *s);
size_t	ft_strlen(const char *s);
size_t	ft_strlenc(const char *s, char c);
size_t	ft_splitlen(char **spl);

// utils_dup.c
char	*ft_strdup(const char *s);
char	*ft_strcdup(const char *s, char c);

// utils_join.c
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strjoinc(const char *s1, const char *s2, char c);
char	*ft_strjoin2(char *s1, const char *s2);
char	*ft_strjoinc2(char *s1, const char *s2, char c);

// utils_cmp.c
int		ft_strcmp(const char *s1, const char *s2);

// utils_valid.c
int		contains(const char *s, char c);
int		scontains(const char *s, const char *c);
int		is_num(char c);
int		valid_name(const char *s, char c);
int		valid_numstr(const char *s);

// utils_mem.c
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

// utils_split.c
void	*split_free(char **spl);
char	**split(char const *str, char c);

// utils_qsplit.c
char	**qsplit(char const *str);

// utils_chr.c
char	*ft_strchr(char *str, char c);
int		ft_strchri(char *str, char c);

// utils_atoi.c
int		ft_atoi(const char *s);
int64_t	ft_atoi_error(const char *s, int *valid);

// utils_itoa.c
char	*ft_itoa(int n);

#endif
