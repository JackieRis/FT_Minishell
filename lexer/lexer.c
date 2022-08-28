/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 23:49:47 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/29 13:44:05 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_empty(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!contains(WSPACE, str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_empty_pipe(t_pctrl *ctrl, t_token *t)
{
	if (!t)
		return (0);
	t = t->next;
	while (t)
	{
		if (is_empty(t->str.s))
		{
			ctrl->err = 259;
			return (1);
		}
		t = t->next;
	}
	return (0);
}

static void	parse_line(t_pctrl *ctrl, t_env *e)
{
	t_token		*tmp;
	t_io		*io;

	ctrl->pipes = pipes_split(ctrl, ctrl->curr_line);
	if (ctrl->err > 0 || check_empty_pipe(ctrl, ctrl->pipes))
	{
		e->lastcode = pipes_err(ctrl->err);
		return ;
	}
	tmp = ctrl->pipes;
	while (tmp)
	{
		io = NULL;
		if (parse_redir(tmp->str.s, e, &io) < 0)
		{
			ctrl->err = e->lastcode;
			clean_io(io);
			break ;
		}
		append_cmd(&ctrl->cmd, new_cmd(&tmp->str, io, e));
		tmp = tmp->next;
	}
	if (ctrl->err != 0)
		clean_cmd(ctrl->cmd);
}

static char	*pick_prompt(void)
{
	return ("minishell-v1.0$ ");
}

t_pctrl	prompt_user(t_env *e)
{
	t_pctrl	ctrl;

	ft_memset(&ctrl, 0, sizeof(t_pctrl));
	ctrl.full_line = readline(pick_prompt());
	if (!ctrl.full_line)
		return (ctrl);
	ctrl.curr_line = ft_strjoin(ctrl.full_line, " ");
	if (is_empty(ctrl.full_line) || !ctrl.curr_line)
		return (ctrl);
	parse_line(&ctrl, e);
	clean_token(ctrl.pipes);
	return (ctrl);
}
