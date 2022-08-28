/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 01:33:01 by aberneli          #+#    #+#             */
/*   Updated: 2022/02/16 15:06:10 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	bi_echo_ext(char **argv, int i, int len)
{
	while (i < len)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (i < len - 1)
			write(1, " ", 1);
		i++;
	}
}

int	bi_echo(t_env *env, char **argv, int child)
{
	int	i;
	int	flag;
	int	len;

	(void)env;
	flag = 0;
	i = 1;
	while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		i++;
		flag = 1;
	}
	len = ft_splitlen(argv);
	bi_echo_ext(argv, i, len);
	if (!flag)
		write(1, "\n", 1);
	if (child)
		exit(0);
	return (0);
}
