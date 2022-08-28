/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 02:27:18 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/02/18 16:36:16 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <utils.h>
#include <stdio.h>

char	**env_split(t_env *e)
{
	t_envlst	*tmp;
	char		**s;
	int			i;

	tmp = e->lst;
	i = 0;
	s = malloc(sizeof(char *) * (e->size + 1));
	if (!s)
		return (NULL);
	while (tmp)
	{
		if (tmp->value)
		{
			s[i] = ft_strjoinc(tmp->name, tmp->value, '=');
			i++;
		}
		tmp = tmp->next;
	}
	s[i] = NULL;
	return (s);
}
