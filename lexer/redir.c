/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:36:59 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/23 17:25:09 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_redir	redir_type(char *s, size_t *i)
{
	if (s[*i] == '>')
	{
		(*i)++;
		if (s[*i] == '>')
		{
			(*i)++;
			return (REDIR_APPEND);
		}
		return (REDIR_OUT);
	}
	(*i)++;
	if (s[*i] == '<')
	{
		(*i)++;
		return (REDIR_HEREDOC);
	}
	return (REDIR_IN);
}

void	extract_redir_ext(char *s, size_t *i)
{
	char	mode;

	mode = 0;
	while (s[*i] && (contains(IDENTIFIER_STR, s[*i]) \
		|| (contains(IDENTIFIER_QSTR, s[*i]) && mode)))
	{
		if (!mode && (s[*i] == '"' || s[*i] == '\''))
			mode = s[*i];
		else if (mode && s[*i] == mode)
			mode = 0;
		(*i)++;
	}
}

char	*extract_redir_id(char *s, size_t len, t_env *e)
{
	char	*identifier;

	identifier = malloc(len + 1);
	if (!identifier)
	{
		e->lastcode = ft_printf(2, 255, "minishell: Cannot allocate memory\n");
		return (NULL);
	}
	ft_memcpy(identifier, s, len);
	identifier[len] = '\0';
	return (identifier);
}

int	extract_redir(char *s, size_t *i, t_env *e, t_io **io)
{
	t_redir	redir;
	size_t	start;
	size_t	id_start;
	char	*identifier;

	start = *i;
	redir = redir_type(s, i);
	while (s[*i] && contains(WSPACE, s[*i]))
		(*i)++;
	if (!s[*i] || !contains(IDENTIFIER_STR, s[*i]))
	{
		e->lastcode = ft_printf(2, 258, \
		"minishell: syntax error: invalid identifier for redirection\n");
		return (-1);
	}
	id_start = *i;
	extract_redir_ext(s, i);
	identifier = extract_redir_id(&s[id_start], (*i) - id_start, e);
	if (!identifier)
		return (-1);
	ft_memset(&s[start], ' ', (*i) - start);
	return (append_io(io, new_io(redir, identifier, 1, e)));
}

int	parse_redir(char *s, t_env *e, t_io **tmp)
{
	size_t	i;
	char	mode;

	i = 0;
	mode = 0;
	while (s[i])
	{
		if (!mode && (s[i] == '"' || s[i] == '\''))
			mode = s[i];
		else if (mode && s[i] == mode)
			mode = 0;
		if (!mode && (s[i] == '>' || s[i] == '<'))
		{
			if (extract_redir(s, &i, e, tmp) < 0)
				return (-1);
		}
		else
			i++;
	}
	return (0);
}
