/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:51:30 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 23:10:04 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	deathfla_update(t_philo *p)
{
	int	n;

	n = p->phi->index;
	pthread_mutex_lock(&(p->pargs->lock_df));
	if (p->pargs->death_flag == 0)
	{
		pthread_mutex_lock(&(p->pargs->prt_lock));
		printf("%lu %d died\n", timepass(p->pargs->current), n);
		p->pargs->death_flag = 1;
		pthread_mutex_unlock(&(p->pargs->prt_lock));
	}
	pthread_mutex_unlock(&(p->pargs->lock_df));
}

void	*philo_death_handler(void *t)
{
	t_philo	*p;

	p = (t_philo *)t;
	pthread_mutex_lock(&(p->phi->lt_eat_mtx));
	p->phi->last_time_eat = p->pargs->current;
	pthread_mutex_unlock(&(p->phi->lt_eat_mtx));
	while (1)
	{
		pthread_mutex_lock(&(p->phi->lt_eat_mtx));
		if ((get_time_ms() - p->phi->last_time_eat > p->pargs->phi_d))
		{
			pthread_mutex_unlock(&(p->phi->lt_eat_mtx));
			break ;
		}
		(pthread_mutex_unlock(&(p->phi->lt_eat_mtx)), usleep(500));
		pthread_mutex_lock(&(p->phi->n_eat_mtx));
		if (p->phi->n_eat == p->pargs->phi_ne)
		{
			pthread_mutex_unlock(&(p->phi->n_eat_mtx));
			return (NULL);
		}
		(pthread_mutex_unlock(&(p->phi->n_eat_mtx)), usleep(200));
	}
	deathfla_update(p);
	return (NULL);
}
