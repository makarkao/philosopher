/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:49:57 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 12:03:36 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	clean_philo(t_philo **p)
{
	int	i;
	int	n;

	n = p[0]->pargs->phi_n;
	free(p[0]->pargs->fork);
	free(p[0]->pargs);
	i = 0;
	while (i < n)
	{
		free(p[i]->phi);
		i++;
	}
	i = 0;
	while (i < n)
	{
		free(p[i]);
		i++;
	}
	free(p);
}

void	free_philo(t_philo **p, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(p[i]->phi);
		free(p[i]);
		i++;
	}
}
