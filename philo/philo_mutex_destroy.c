/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex_destroy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:18:26 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 12:06:52 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	destroy_fork(t_philo **p, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&(p[0]->pargs->fork[i++]));
}

void	destroy_shmutexes(t_philo **p)
{
	int	n;

	n = p[0]->pargs->phi_n;
	destroy_fork(p, n);
	pthread_mutex_destroy(&(p[0]->pargs->lock_df));
	pthread_mutex_destroy(&(p[0]->pargs->prt_lock));
}

void	destroy_pmutexes(t_philo **p, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&(p[i]->phi->n_eat_mtx));
		pthread_mutex_destroy(&(p[i]->phi->lt_eat_mtx));
		i++;
	}
}

void	destroy_mutexes(t_philo **p)
{
	int	n;

	n = p[0]->pargs->phi_n;
	destroy_pmutexes(p, n);
	destroy_shmutexes(p);
}
