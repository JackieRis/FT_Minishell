/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:01:49 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/25 14:08:44 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	status_to_error(int status)
{
	if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	if (WIFSIGNALED(status))
	{
		return (WTERMSIG(status) + 128);
	}
	return (1);
}

void	wait_pid(t_cmd *t, t_env *e)
{
	int	status;

	while (t)
	{
		status = 0;
		if (waitpid(t->f, &status, 0) < 0)
			ft_printf(2, 0, "minishell: %s\n", strerror(errno));
		else
			e->lastcode = status_to_error(status);
		t = t->next;
	}
}
