/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:53:32 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/29 13:14:48 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <utils.h>
#include <stdio.h>

void	env_display(t_env *e)
{
	t_envlst	*tmp;

	tmp = e->lst;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

char	*env_get(t_env *e, char *name)
{
	t_envlst	*tmp;

	if (!name)
		return (NULL);
	if (ft_strcmp(name, "?") == 0)
	{
		free(e->codestr);
		e->codestr = ft_itoa(e->lastcode);
		return (e->codestr);
	}
	tmp = e->lst;
	while (tmp && ft_strcmp(name, tmp->name) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	if (ft_strcmp(name, tmp->name) == 0)
		return (tmp->value);
	return (NULL);
}

static t_envquery	env_query_dollar(void)
{
	t_envquery	q;

	ft_memset(&q, 0, sizeof(t_envquery));
	q.dollar = 1;
	return (q);
}

t_envquery	env_query(t_env *e, char *name)
{
	t_envquery	q;
	t_str		s;

	if (!name[1] || contains(WSPACE, name[1]) || contains("\"'", name[1]))
		return (env_query_dollar());
	ft_memset(&q, 0, sizeof(t_envquery));
	q.nlen = 1;
	s = str_new();
	while (name[q.nlen] && contains(VALID_NAME_STR, name[q.nlen]))
	{
		str_add(&s, name[q.nlen]);
		if (q.nlen == 1 && (is_num(name[q.nlen]) || name[q.nlen] == '?'))
		{
			q.nlen = 2;
			break ;
		}
		q.nlen++;
	}
	q.var = env_get(e, s.s);
	q.nlen -= 1;
	free(s.s);
	return (q);
}
