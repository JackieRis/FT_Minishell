/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 00:40:02 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/02/19 17:02:01 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <utils.h>

void	env_export(t_env *e, char *name, char *value)
{
	t_envlst	*tmp;

	tmp = e->lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			if (value)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
			}
			return ;
		}
		tmp = tmp->next;
	}
	tmp = e->lst;
	e->lst = new_lst(ft_strdup(name), ft_strdup(value));
	e->lst->next = tmp;
	e->size++;
}

static void	env_swap(t_key_val *a, t_key_val *b)
{
	char	*tmp;

	tmp = a->name;
	a->name = b->name;
	b->name = tmp;
	tmp = a->value;
	a->value = b->value;
	b->value = tmp;
}

static void	env_key_val(t_key_val *k, size_t size)
{
	size_t	i;
	size_t	j;

	i = size - 1;
	while (i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(k[j].name, k[j + 1].name) > 0)
				env_swap(&k[j], &k[j + 1]);
			j++;
		}
		i--;
	}
}

static void	env_key_fill(t_env *e, t_key_val *k, size_t size)
{
	size_t		i;
	t_envlst	*tmp;

	i = 0;
	tmp = e->lst;
	while (tmp && i < size)
	{
		k[i].name = tmp->name;
		k[i].value = tmp->value;
		tmp = tmp->next;
		i++;
	}
}

void	env_print_order(t_env *e)
{
	t_key_val	*k;
	size_t		i;
	size_t		size;

	size = e->size;
	k = malloc(sizeof(t_key_val) * size);
	if (!k)
		return ;
	env_key_fill(e, k, size);
	env_key_val(k, size);
	i = 0;
	while (i < size)
	{
		if (!k[i].value)
			printf("declare -x %s\n", k[i].name);
		else
			printf("declare -x %s=\"%s\"\n", k[i].name, k[i].value);
		i++;
	}
	free (k);
}
