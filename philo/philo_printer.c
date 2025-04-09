/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:53:38 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 10:53:39 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	print_state(int state, int mask, t_philo *p)
{
	pthread_mutex_lock(&(p->pargs->prt_lock));
	if (p->pargs->death_flag == 0)
	{
		if (state == 1)
			printf("%lu %d has taken a fork\n", timepass(p->pargs->current),
				p->phi->index);
		if (state == 2)
			printf("%lu %d is eating\n", timepass(p->pargs->current),
				p->phi->index);
		if (state == 3)
			printf("%lu %d is sleeping\n", timepass(p->pargs->current),
				p->phi->index);
		if (state == 4)
			printf("%lu %d is thinking\n", timepass(p->pargs->current),
				p->phi->index);
	}
	else
		return (pthread_mutex_unlock(&(p->pargs->prt_lock)), unlock_forks(p,
				mask), 0);
	pthread_mutex_unlock(&(p->pargs->prt_lock));
	return (1);
}
