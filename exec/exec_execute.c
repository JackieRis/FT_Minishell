/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:16:57 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/25 14:38:52 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	explicit_path_exec(t_cmd *t, t_exec *exe)
{
	int		errnum;

	if (execve(t->args[0], t->args, exe->env) < 0)
	{
		errnum = errno;
		if (errnum != ENOENT)
			exit(ft_printf(2, 126, \
				"minishell: %s: %s\n", t->args[0], strerror(errnum)));
		exit(ft_printf(2, 127, \
			"minishell: %s: %s\n", t->args[0], strerror(errnum)));
	}
}

static void	pathless_exec(t_cmd *t, t_exec *exe, char *cmd_save)
{
	int		errnum;

	t->args[0] = cmd_save;
	if (execve(t->args[0], t->args, exe->env) < 0)
	{
		errnum = errno;
		if (errnum != ENOENT)
			exit(ft_printf(2, 126, \
				"minishell: %s: %s\n", t->args[0], strerror(errnum)));
		exit(ft_printf(2, 127, \
			"minishell: %s: command not found\n", cmd_save));
	}
}

static void	err_handling(t_error *err, char *arg)
{
	if (errno == ENOENT)
	{
		if (err->err == 0)
		{
			err->err = 127;
			err->errpath = ft_strdup(arg);
			err->errnum = errno;
		}
	}
	else
	{
		if (err->err != 126)
		{
			err->err = 126;
			free(err->errpath);
			err->errpath = ft_strdup(arg);
			err->errnum = errno;
		}
	}
}

static void	regular_exec(t_cmd *t, t_exec *exe, char *cmd_save)
{
	t_error	err;
	char	*path;
	int		i;

	err.err = 0;
	err.errpath = NULL;
	i = 0;
	while (exe->path[i])
	{
		path = ft_strjoinc(exe->path[i], cmd_save, '/');
		t->args[0] = path;
		if (execve(t->args[0], t->args, exe->env) < 0)
			err_handling(&err, t->args[0]);
		free(t->args[0]);
		i++;
	}
	if (err.err == 126)
		ft_printf(2, err.err, \
			"minishell: %s: %s\n", err.errpath, strerror(err.errnum));
	else
		ft_printf(2, err.err, \
			"minishell: %s: command not found\n", cmd_save);
	free(cmd_save);
	free(err.errpath);
	exit(err.err);
}

void	execute_cmd(t_cmd *t, t_exec *exe)
{
	char	*cmd_save;

	if (!t->args[0])
		exit(0);
	if (ft_strchr(t->args[0], '/'))
		explicit_path_exec(t, exe);
	cmd_save = t->args[0];
	t->args[0] = NULL;
	if (!exe->pathvar || ft_splitlen(exe->path) == 0)
		pathless_exec(t, exe, cmd_save);
	regular_exec(t, exe, cmd_save);
}
