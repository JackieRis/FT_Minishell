/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:13:54 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/23 12:06:48 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*new_token(void)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->next = NULL;
	t->str = str_new();
	if (!t->str.s)
	{
		free(t);
		return (NULL);
	}
	return (t);
}

void	append_token(t_token **beg, t_token *add)
{
	t_token	*tmp;

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

void	clean_token(t_token *tok)
{
	t_token	*tmp;

	if (!tok)
		return ;
	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp->str.s);
		free(tmp);
	}
}
