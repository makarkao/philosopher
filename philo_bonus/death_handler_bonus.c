/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:11:11 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 14:33:44 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static int	check_death_timer(t_philo *p)
{
	sem_wait(p->last_teat[p->id]);
	if ((get_time_ms() - p->last_time_eat) > p->phi_d)
	{
		sem_wait(p->w_death);
		sem_wait(p->print);
		printf("%lu %d died\n", time_pass_ms(p->current), p->id + 1);
		sem_post(p->death);
		return (1);
	}
	sem_post(p->last_teat[p->id]);
	return (0);
}

static int	check_ntimes_eat(t_philo *p)
{
	sem_wait(p->eat_counter[p->id]);
	if (p->n_eat >= p->phi_ne)
	{
		sem_post(p->eat_counter[p->id]);
		return (1);
	}
	sem_post(p->eat_counter[p->id]);
	usleep(500);
	return (0);
}

void	*death_handler(void *t)
{
	t_philo	*p;

	p = (t_philo *)t;
	while (1)
	{
		if (check_death_timer(p))
			break ;
		usleep(1000);
		if (p->phine_flag == 1 && check_ntimes_eat(p))
			break ;
	}
	return (NULL);
}

void	*kill_handler(void *t)
{
	int		i;
	t_philo	*p;

	i = 0;
	p = (t_philo *)t;
	sem_wait(p->death);
	sem_wait(p->finish_flg);
	if (p->finish_falg == 0)
	{
		p->finish_falg = 1;
		while (i < p->phi_n)
		{
			kill(p->philo[i], SIGKILL);
			i++;
		}
	}
	sem_post(p->finish_flg);
	return (NULL);
}
