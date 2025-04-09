/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:29:57 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 14:37:56 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static int	is_num(char c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

int	is_numeric(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_num(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	leninteger(unsigned int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int x)
{
	char			*str;
	int				i;
	unsigned int	n;

	n = x;
	i = leninteger(n) + 1;
	if (x <= 0)
	{
		n = -x;
		i = leninteger(n) + 2;
	}
	str = malloc(i * sizeof(char));
	if (!str)
		return (NULL);
	str[--i] = '\0';
	if (n == 0)
		str[--i] = '0';
	if (x < 0)
		str[0] = '-';
	while (n != 0)
	{
		str[--i] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
