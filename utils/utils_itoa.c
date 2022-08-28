/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_itoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:17:00 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/23 15:17:01 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_get_num_len(int nbr)
{
	int				len;
	unsigned int	check;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		len = 1;
		check = -nbr;
	}
	else
		check = nbr;
	while (check > 0)
	{
		check /= 10;
		len++;
	}
	return (len);
}

static void	ft_itoa_base_fill(char *str, unsigned int nbr, int nlen)
{
	int		i;

	i = nlen - 1;
	while (nbr > 0)
	{
		str[i] = (nbr % 10) + '0';
		nbr /= 10;
		i--;
	}
	str[nlen] = '\0';
}

char	*ft_itoa(int n)
{
	char	*result;
	int		num_len;

	num_len = ft_get_num_len(n);
	result = malloc(num_len + 1);
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
		ft_itoa_base_fill(result, -n, num_len);
	}
	else
	{
		result[0] = '0';
		ft_itoa_base_fill(result, n, num_len);
	}
	return (result);
}
