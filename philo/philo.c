/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:19:20 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 13:40:08 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_philo	**p;
	int		i;
	int		rvalue;

	i = 1;
	p = NULL;
	if (ac != 5 && ac != 6)
		return (1);
	while (i < ac)
	{
		if (!is_numeric(av[i]) || ft_atoi(av[i]) > INT_MAX || !av[i][0])
			return (p_rror(0), 1);
		i++;
	}
	p = init_philo(p, av, ac);
	if (!p)
		return (1);
	rvalue = manage_threads(p);
	return (rvalue);
}
