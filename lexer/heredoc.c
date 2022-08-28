/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 08:31:39 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/29 13:44:19 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include <ms_signal.h>

char	*expand_heredoc(char *s, t_env *e)
{
	t_envquery	q;
	t_str		res;
	size_t		i;

	res = str_new();
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			q = env_query(e, &s[i]);
			if (q.dollar)
				str_add(&res, '$');
			else
				str_append(&res, q.var);
			i += q.nlen;
		}
		else
			str_add(&res, s[i]);
		i++;
	}
	free(s);
	return (res.s);
}

static char	*parse_copy(char *d)
{
	size_t	i;
	size_t	j;
	int		mode;
	char	*res;

	res = malloc(ft_strlen(d) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	mode = 0;
	while (d[j])
	{
		if (mode == 0 && (d[j] == '"' || d[j] == '\''))
			mode = d[j];
		else if ((mode == '"' && d[j] == '"') || (mode == '\'' && d[j] == '\''))
			mode = 0;
		else
			res[i++] = d[j];
		j++;
	}
	res[i] = '\0';
	free(d);
	return (res);
}

void	status_cleanup(t_env *e, char **doc)
{
	if (g_status < 128)
		return ;
	free(*doc);
	*doc = NULL;
	dup2(g_status - 128, 0);
	g_status = 4;
	e->lastcode = 1;
}

char	*parse_heredoc(char *delim, t_env *e, int quote_flag)
{
	char	*doc;
	char	*line;

	delim = parse_copy(delim);
	doc = ft_strdup("");
	g_status = 3;
	line = readline("heredoc> ");
	while (line)
	{
		if (ft_strcmp(line, delim) == 0 || g_status >= 128)
			break ;
		if (!quote_flag)
			line = expand_heredoc(line, e);
		doc = ft_strjoin2(ft_strjoin2(doc, line), "\n");
		free(line);
		line = readline("heredoc> ");
	}
	free(delim);
	free(line);
	status_cleanup(e, &doc);
	return (doc);
}
