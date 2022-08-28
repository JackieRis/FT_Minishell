/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 21:43:39 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/26 10:05:55 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <utils.h>

t_envlst	*new_lst(char *name, char *value)
{
	t_envlst	*e;

	e = malloc(sizeof(t_envlst));
	if (!e)
		return (NULL);
	e->name = name;
	e->value = value;
	e->next = NULL;
	return (e);
}

static void	parsing(t_env *e, char *line)
{
	t_envlst	*tmp;
	int			i;

	if (!ft_strchr(line, '='))
		tmp = new_lst(ft_strdup(line), NULL);
	else
	{
		i = ft_strlenc(line, '=');
		tmp = new_lst(ft_strcdup(line, '='), ft_strdup(&line[i + 1]));
	}
	tmp->next = e->lst;
	e->lst = tmp;
}

static void	env_shlvl(t_env *e)
{
	char	*lvl;
	char	*newlvl;
	int		val;
	int		dummy;

	lvl = env_get(e, "SHLVL");
	dummy = 0;
	if (!lvl)
	{
		env_export(e, "SHLVL", "1");
		return ;
	}
	val = ft_atoi_error(lvl, &dummy) + 1;
	newlvl = ft_itoa(val);
	env_export(e, "SHLVL", newlvl);
	free(newlvl);
}

t_env	env_init(char **envp)
{
	t_env	e;
	int		i;

	e.pwd = getcwd(NULL, 0);
	e.size = ft_splitlen(envp);
	e.codestr = NULL;
	e.lst = NULL;
	e.lastcode = 0;
	i = e.size;
	while (--i >= 0)
		parsing(&e, envp[i]);
	env_export(&e, "OLDPWD", NULL);
	env_shlvl(&e);
	return (e);
}
