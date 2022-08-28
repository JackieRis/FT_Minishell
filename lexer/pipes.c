/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:14:36 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/24 11:06:25 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	pipes_split_next(char *line, size_t *i, t_str *s)
{
	char	mode;

	mode = 0;
	while (line[*i] && !(line[*i] == '|' && mode == 0))
	{
		if (!mode)
		{
			if (line[*i] == '"' || line[*i] == '\'')
				mode = line[*i];
		}
		else if (mode)
		{
			if (line[*i] == mode)
				mode = 0;
		}
		str_add(s, line[*i]);
		(*i)++;
	}
	return (mode);
}

t_token	*pipes_split(t_pctrl *ctrl, char *line)
{
	t_token		*lst;
	t_token		*tmp;
	size_t		i;

	lst = NULL;
	i = 0;
	while (line[i] && ctrl->err == 0)
	{
		tmp = new_token();
		if (!tmp)
		{
			ctrl->err = 255;
			break ;
		}
		ctrl->err = pipes_split_next(line, &i, &tmp->str);
		if (!tmp->str.s)
			ctrl->err = 255;
		append_token(&lst, tmp);
		if (line[i])
			i++;
	}
	return (lst);
}

int	pipes_err(int err)
{
	if (err == '"' || err == '\'')
		return (ft_printf(2, 258, \
		"minishell: unexpected EOF while looking for matching `%c`\n", err));
	else if (err == 255)
		return (ft_printf(2, 255, "minishell: Cannot allocate memory\n"));
	else if (err == 259)
		return (ft_printf(2, 258, \
		"minishell: syntax error near unexpected token `|`\n"));
	return (1);
}
