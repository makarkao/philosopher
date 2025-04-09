/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_est.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:01:41 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 13:05:30 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	unlock_forks(t_philo *p, int mask)
{
	if (mask != 0 && mask != 1)
		return ;
	pthread_mutex_unlock(p->phi->fork_1);
	if (mask)
		pthread_mutex_unlock(p->phi->fork_2);
}

static void	solo_philo(t_philo *p)
{
	pthread_mutex_lock(p->phi->fork_1);
	if (!print_state(1, 0, p))
		return ;
	pthread_mutex_unlock(p->phi->fork_1);
}

static void	philo_eat_hanler(t_philo *p)
{
	pthread_mutex_lock(p->phi->fork_1);
	if (!print_state(1, 0, p))
		return ;
	pthread_mutex_lock(p->phi->fork_2);
	if (!print_state(1, 1, p))
		return ;
	if (!print_state(2, 1, p))
		return ;
	pthread_mutex_lock(&(p->phi->lt_eat_mtx));
	p->phi->last_time_eat = get_time_ms();
	pthread_mutex_unlock(&(p->phi->lt_eat_mtx));
	usleep(p->pargs->phi_e * 1000);
	unlock_forks(p, 1);
}

static void	philo_st_handler(t_philo *p)
{
	if (!print_state(3, 2, p))
		return ;
	usleep(p->pargs->phi_s * 1000);
	if (!print_state(4, 2, p))
		return ;
	usleep(p->pargs->phi_t * 1000);
	pthread_mutex_lock(&(p->phi->n_eat_mtx));
	p->phi->n_eat++;
	pthread_mutex_unlock(&(p->phi->n_eat_mtx));
}

void	*philo_est_handler(void *t)
{
	t_philo	*p;
	int		n;

	(1) && (p = (t_philo *)t, n = p->pargs->phi_n);
	if (n == 1)
		return (solo_philo(p), NULL);
	pthread_mutex_lock(&(p->phi->n_eat_mtx));
	pthread_mutex_lock(&(p->pargs->lock_df));
	while (p->pargs->death_flag == 0 && (p->pargs->phi_ne == -1
			|| (p->phi->n_eat < p->pargs->phi_ne)))
	{
		pthread_mutex_unlock(&(p->pargs->lock_df));
		pthread_mutex_unlock(&(p->phi->n_eat_mtx));
		philo_eat_hanler(p);
		philo_st_handler(p);
		pthread_mutex_lock(&(p->phi->n_eat_mtx));
		pthread_mutex_lock(&(p->pargs->lock_df));
	}
	pthread_mutex_unlock(&(p->pargs->lock_df));
	pthread_mutex_unlock(&(p->phi->n_eat_mtx));
	return (NULL);
}
