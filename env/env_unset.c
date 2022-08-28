/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 01:06:10 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/23 15:19:37 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <utils.h>

t_envlst	*env_delete(t_envlst *e)
{
	t_envlst	*tmp;

	tmp = e->next;
	free(e->name);
	free(e->value);
	free(e);
	return (tmp);
}

void	env_unset(t_env *e, char *name)
{
	t_envlst	*tmp;
	t_envlst	*prev;

	if (e->size == 0)
		return ;
	prev = NULL;
	tmp = e->lst;
	while (ft_strcmp(name, tmp->name) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
		if (!tmp)
			return ;
	}
	if (!prev)
		e->lst = env_delete(tmp);
	else
		prev->next = env_delete(tmp);
	e->size--;
}

void	env_destroy(t_envlst *e)
{
	while (e)
		e = env_delete(e);
}
