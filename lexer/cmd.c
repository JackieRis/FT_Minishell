/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:38:34 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/24 16:50:47 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_cmd	*new_cmd(t_str *str, t_io *redir, t_env *e)
{
	t_cmd	*cmd;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->f = -1;
	cmd->next = NULL;
	cmd->args = qsplit(str->s);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	i = 0;
	while (cmd->args[i])
	{
		cmd->args[i] = expand_str(cmd->args[i], e);
		i++;
	}
	cmd->builtin = which_builtin(cmd->args[0]);
	cmd->redirections = redir;
	return (cmd);
}

void	append_cmd(t_cmd **beg, t_cmd *add)
{
	t_cmd	*tmp;

	if (!add)
		return ;
	if (!(*beg))
	{
		*beg = add;
		return ;
	}
	tmp = *beg;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add;
}

void	clean_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		clean_io(tmp->redirections);
		split_free(tmp->args);
		free(tmp);
	}
}
