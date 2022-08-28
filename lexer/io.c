/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:23:10 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/25 16:04:19 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_io	*new_io(t_redir type, char *file, int fdnbr, t_env *e)
{
	t_io	*redir;

	redir = malloc(sizeof(t_io));
	if (!redir)
		return (NULL);
	redir->next = NULL;
	redir->fdnbr = fdnbr;
	redir->type = type;
	if (type != REDIR_HEREDOC)
		redir->file = expand_str(file, e);
	else
		redir->file = parse_heredoc(file, e, \
		(contains(file, '"') || contains(file, '\'')));
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

int	append_io(t_io **beg, t_io *add)
{
	t_io	*tmp;

	if (!add)
		return (-1);
	if (!(*beg))
	{
		*beg = add;
		return (0);
	}
	tmp = *beg;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add;
	return (0);
}

void	clean_io(t_io *io)
{
	t_io	*tmp;

	if (!io)
		return ;
	while (io)
	{
		tmp = io;
		io = io->next;
		free(tmp->file);
		free(tmp);
	}
}
