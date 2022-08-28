/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:48:57 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/29 13:23:17 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	bi_env(t_env *env, char **argv, int child)
{
	(void)argv;
	env_display(env);
	if (child)
		exit (0);
	return (0);
}

int	bi_unset(t_env *env, char **argv, int child)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (argv[i])
	{
		if (!valid_name(argv[1], '\0'))
		{
			error = 1;
			ft_printf(2, 1, \
			"minishell: unset: `%s': not a valid identifier\n", argv[i]);
		}
		else
			env_unset(env, argv[i]);
		i++;
	}
	if (child)
		exit (error);
	return (error);
}

static void	split_line(t_env *e, char *line)
{
	int		i;
	char	*name;
	char	*value;

	value = NULL;
	if (!ft_strchr(line, '='))
		name = ft_strdup(line);
	else
	{
		i = ft_strlenc(line, '=');
		name = ft_strcdup(line, '=');
		value = ft_strdup(&line[i + 1]);
	}
	env_export(e, name, value);
	free(name);
	free(value);
}

int	bi_export(t_env *env, char **argv, int child)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	if (!argv[i])
		env_print_order(env);
	while (argv[i])
	{
		if (argv[i][0] == '=' || !valid_name(argv[i], '='))
		{
			error = 1;
			ft_printf(2, 1, \
			"minishell: export: `%s': not a valid identifier\n", argv[i]);
		}
		split_line(env, argv[i]);
		i++;
	}
	if (child)
		exit (error);
	return (error);
}
