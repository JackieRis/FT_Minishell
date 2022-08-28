/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 23:06:30 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/26 09:07:54 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdio.h>

static void	exec_close_pipe(int	*fd, int i)
{
	if (!i)
		return ;
	if (close(fd[0]) < 0)
		ft_printf(2, 1, "minishell: %s\n", strerror(errno));
	if (close(fd[1]) < 0)
		ft_printf(2, 1, "minishell: %s\n", strerror(errno));
}

//compter nombre de commande

static int	n_cmd(t_cmd *t)
{
	int	i;

	i = 0;
	while (t)
	{
		t = t->next;
		i++;
	}
	return (i);
}

static void	exec_pipe(t_cmd *t, t_env *e, t_exec *exe, int n)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = t;
	while (i < n)
	{
		if (i < n - 1 && pipe(exe->fdout) == -1)
			ft_printf(2, 1, "minishell: %s\n", strerror(errno));
		t->f = fork();
		if (t->f == 0)
			exec_process(t, exe, e, i);
		else if (t->f < 0)
			ft_printf(2, 1, "minishell: %s\n", strerror(errno));
		exec_close_pipe(exe->fdin, i > 0);
		ft_memcpy(exe->fdin, exe->fdout, sizeof(int) * 2);
		t = t->next;
		i++;
	}
	wait_pid(tmp, e);
}

//fonction mère d'éxecution

void	exec(t_cmd *t, t_env *e)
{
	t_exec	exe;
	int		n;

	exe.env = env_split(e);
	exe.pathvar = env_get(e, "PATH");
	exe.path = split(exe.pathvar, ':');
	n = n_cmd(t);
	if (n == 0)
		return ;
	if (n > 1)
		exec_pipe(t, e, &exe, n);
	else
	{
		if (!t->builtin)
			e->lastcode = solo_cmd(t, &exe);
		else
			bi_parentexec(t, e);
	}
	split_free(exe.env);
	split_free(exe.path);
}
