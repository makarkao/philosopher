/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_handler_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:12:39 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 14:34:40 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	solo_philo(t_philo *p)
{
	sem_wait(p->forks);
	sem_wait(p->print);
	printf("%lu %d has taken a fork\n", time_pass_ms(p->current), p->id + 1);
	sem_post(p->print);
	sem_wait(p->forks);
}

static void	eat_handler(t_philo *p)
{
	sem_wait(p->eat);
	sem_wait(p->forks);
	sem_wait(p->print);
	printf("%lu %d has taken a fork\n", time_pass_ms(p->current), p->id + 1);
	sem_post(p->print);
	sem_wait(p->forks);
	sem_wait(p->print);
	printf("%lu %d has taken a fork\n", time_pass_ms(p->current), p->id + 1);
	sem_post(p->print);
	sem_wait(p->last_teat[p->id]);
	p->last_time_eat = get_time_ms();
	sem_post(p->last_teat[p->id]);
	sem_wait(p->print);
	printf("%lu %d is eating\n", time_pass_ms(p->current), p->id + 1);
	sem_post(p->print);
	usleep(p->phi_e * 1000);
	sem_post(p->forks);
	sem_post(p->forks);
	sem_post(p->eat);
}

static void	sleep_think_handler(t_philo *p)
{
	sem_wait(p->print);
	printf("%lu %d is sleeping\n", time_pass_ms(p->current), p->id + 1);
	sem_post(p->print);
	usleep(p->phi_s * 1000);
	sem_wait(p->print);
	printf("%lu %d is thinking\n", time_pass_ms(p->current), p->id + 1);
	sem_post(p->print);
	usleep(p->t_phi * 1000);
	if (p->phine_flag == 1)
	{
		sem_wait(p->eat_counter[p->id]);
		p->n_eat++;
		sem_post(p->eat_counter[p->id]);
	}
}

void	philo_handler(t_philo *p)
{
	t_psems_name	n;
	pthread_t		die;

	private_sems_init(p, &n);
	p->last_time_eat = get_time_ms();
	if (pthread_create(&die, NULL, death_handler, p))
		exit((private_sems_dest(p, &n), p_error(3, p), sem_post(p->death),
				clean_philo(p), 1));
	if (p->phi_n == 1)
		solo_philo(p);
	else
	{
		while (p->phine_flag == 0 || (p->phine_flag == 1
				&& p->n_eat < p->phi_ne))
		{
			eat_handler(p);
			sleep_think_handler(p);
		}
	}
	if (pthread_join(die, NULL))
		exit((private_sems_dest(p, &n), p_error(4, p), sem_post(p->death),
				clean_philo(p), 1));
	private_sems_dest(p, &n);
	clean_philo(p);
	exit(0);
}
