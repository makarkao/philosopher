/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:17:48 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 13:38:52 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	create_odd_threads(t_philo **p)
{
	int	i;
	int	n;

	i = 0;
	n = p[0]->pargs->phi_n;
	while (i < n && i % 2 == 0)
	{
		if (pthread_create(&(p[i]->phi->philo), NULL, philo_est_handler, p[i])
			|| pthread_create(&(p[i]->phi->death), NULL, philo_death_handler,
				p[i]))
		{
			pthread_mutex_lock(&(p[i]->pargs->prt_lock));
			p[i]->pargs->death_flag = 1;
			pthread_mutex_unlock(&(p[i]->pargs->prt_lock));
			return (p_error(3, p[i]), 0);
		}
		i += 2;
	}
	return (1);
}

static int	create_even_threads(t_philo **p)
{
	int	i;
	int	n;

	n = p[0]->pargs->phi_n;
	i = 1;
	while (i < n && i % 2 == 1)
	{
		if (pthread_create(&(p[i]->phi->philo), NULL, philo_est_handler, p[i])
			|| pthread_create(&(p[i]->phi->death), NULL, philo_death_handler,
				p[i]))
		{
			pthread_mutex_lock(&(p[i]->pargs->prt_lock));
			p[i]->pargs->death_flag = 1;
			pthread_mutex_unlock(&(p[i]->pargs->prt_lock));
			return (p_error(3, p[i]), 0);
		}
		i += 2;
	}
	return (1);
}

static int	create_threads(t_philo **p)
{
	int	rvalue;

	rvalue = 1;
	if (!create_odd_threads(p))
		rvalue = 0;
	usleep(5000);
	if (!create_even_threads(p))
		rvalue = 0;
	return (rvalue);
}

static int	join_threads(t_philo **p)
{
	int	i;
	int	n;

	i = 0;
	n = p[0]->pargs->phi_n;
	while (i < n)
	{
		if (pthread_join(p[i]->phi->philo, NULL)
			|| pthread_join(p[i]->phi->death, NULL))
		{
			pthread_mutex_lock(&(p[i]->pargs->prt_lock));
			p[i]->pargs->death_flag = 1;
			pthread_mutex_unlock(&(p[i]->pargs->prt_lock));
			return (p_error(4, p[i]), 0);
		}
		i++;
	}
	return (1);
}

int	manage_threads(t_philo **p)
{
	int	rvalue;

	rvalue = 1;
	p[0]->pargs->current = get_time_ms();
	if (create_threads(p))
		rvalue = 0;
	if (join_threads(p))
		rvalue = 0;
	destroy_mutexes(p);
	clean_philo(p);
	return (rvalue);
}
