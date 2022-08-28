/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 01:45:35 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/25 18:53:07 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*cd_path(t_env *env, char *arg, int *flag)
{
	*flag = 0;
	if (!arg)
	{
		*flag = 1;
		return (env_get(env, "HOME"));
	}
	else if (ft_strcmp(arg, "--") == 0)
	{
		*flag = 1;
		return (env_get(env, "HOME"));
	}
	else if (ft_strcmp(arg, "-") == 0)
	{
		*flag = 2;
		return (env_get(env, "OLDPWD"));
	}
	return (arg);
}

static int	fast_return(int code, int child)
{
	if (child)
		exit(code != 0);
	return (code != 0);
}

static int	cd_error(t_env *env, char *argv, char **path, int *flag)
{
	int		code;

	code = 0;
	*path = cd_path(env, argv, flag);
	if (*flag && !(*path))
	{
		if (*flag == 1)
			code = ft_printf(2, 1, "minishell: cd: HOME not set\n");
		else if (*flag == 2)
			code = ft_printf(2, 1, "minishell: cd: OLDPWD not set\n");
		return (code);
	}
	return (code);
}

int	bi_cd(t_env *env, char **argv, int child)
{
	char	*oldpwd;
	char	*tmp;
	char	*path;
	int		flag;

	if (cd_error(env, argv[1], &path, &flag) != 0)
		return (fast_return(1, child));
	if (flag == 1 && (contains(WSPACE, path[0]) || !path[0]))
		return (fast_return(0, child));
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) < 0)
	{
		ft_printf(2, 1, "minishell: cd: %s: %s\n", path, strerror(errno));
		free(oldpwd);
		return (fast_return(1, child));
	}
	tmp = getcwd(NULL, 0);
	env_export(env, "OLDPWD", oldpwd);
	env_export(env, "PWD", tmp);
	free(env->pwd);
	env->pwd = tmp;
	if (flag)
		ft_printf(1, 0, "%s\n", env->pwd);
	free(oldpwd);
	return (fast_return(0, child));
}
