/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:34:44 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/23 15:22:20 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	expand_str_ex(t_str *res, t_env *e, char *s, size_t *i)
{
	t_envquery	q;

	q = env_query(e, &s[*i]);
	if (q.dollar)
		str_add(res, '$');
	else
		str_append(res, q.var);
	*i += q.nlen;
}

char	*expand_str(char *s, t_env *e)
{
	t_str		res;
	size_t		i;
	char		mode;

	res = str_new();
	i = 0;
	mode = 0;
	while (s[i])
	{
		if (!mode && (s[i] == '"' || s[i] == '\''))
			mode = s[i];
		else if (mode && s[i] == mode)
			mode = 0;
		else if (s[i] == '$' && mode != '\'')
			expand_str_ex(&res, e, s, &i);
		else
			str_add(&res, s[i]);
		i++;
	}
	free(s);
	return (res.s);
}
