/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 13:31:32 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/26 09:13:01 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	exit_2(t_env *env, int code)
{
	env_destroy(env->lst);
	free(env->pwd);
	free(env->codestr);
	clear_history();
	tcsetattr(0, TCSANOW, &env->save);
	exit(code);
}

int	bi_exit_ext(char **argv, size_t arglen, t_env *env)
{
	int		valid;
	int		code;

	valid = 1;
	code = ft_atoi_error(argv[1], &valid) % 256;
	if (valid != 1 || !valid_numstr(argv[1]))
	{
		ft_printf(2, 255, \
		"minishell: exit: %s: numeric argument required\n", argv[1]);
		exit_2(env, 255);
	}
	else if (arglen > 2)
	{
		ft_printf(2, 1, "minishell: exit: too many arguments\n");
		return (1);
	}
	exit_2(env, code);
	return (1);
}

int	bi_exit(t_env *env, char **argv, int child)
{
	size_t	arglen;

	(void)child;
	arglen = ft_splitlen(argv);
	write(1, "exit\n", 5);
	if (arglen > 1)
		return (bi_exit_ext(argv, arglen, env));
	exit_2(env, env->lastcode);
	return (env->lastcode);
}
