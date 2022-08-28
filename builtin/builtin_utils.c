/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 01:01:20 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/22 10:23:45 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	which_builtin(const char *name)
{
	if (!name)
		return (0);
	if (ft_strcmp(name, "echo") == 0)
		return (1);
	if (ft_strcmp(name, "cd") == 0)
		return (2);
	if (ft_strcmp(name, "pwd") == 0)
		return (3);
	if (ft_strcmp(name, "export") == 0)
		return (4);
	if (ft_strcmp(name, "unset") == 0)
		return (5);
	if (ft_strcmp(name, "env") == 0)
		return (6);
	if (ft_strcmp(name, "exit") == 0)
		return (7);
	return (0);
}

void	bi_parentexec(t_cmd *t, t_env *e)
{
	int		save[2];

	save[0] = dup(0);
	save[1] = dup(1);
	if (exec_redirection(t->redirections) == 0)
		bi_execute(e, t->args, 0);
	dup2(save[0], 0);
	dup2(save[1], 1);
	close(save[0]);
	close(save[1]);
}

int	bi_execute(t_env *env, char **argv, int child)
{
	static int	(*func[8])(t_env *, char **, int) = \
		{NULL, bi_echo, bi_cd, bi_pwd, bi_export, bi_unset, bi_env, bi_exit};
	int			bi;

	bi = which_builtin(argv[0]);
	if (!bi)
		return (0);
	env->lastcode = (*(func[bi]))(env, argv, child);
	return (1);
}
