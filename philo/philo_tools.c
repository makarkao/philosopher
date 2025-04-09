/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:18:54 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 13:07:53 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	ft_atoi(const char *str)
{
	int			i;
	int			s;
	long long	x;

	i = 0;
	s = 1;
	x = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		x = (str[i] - '0') + (x * 10);
		if (x > LONG_MAX)
			return (LONG_MAX);
		i++;
	}
	return (x * s);
}

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

unsigned long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000UL) + (tv.tv_usec / 1000UL));
}

unsigned long	timepass(unsigned long current)
{
	return (get_time_ms() - current);
}
