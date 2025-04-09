/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_tools_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:13:53 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 14:35:13 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	free_private_names(t_psems_name *n)
{
	free(n->last_eat_sem_name);
	free(n->eat_counter_sem_name);
}

void	private_sems_dest(t_philo *p, t_psems_name *n)
{
	sem_close(p->last_teat[p->id]);
	sem_close(p->eat_counter[p->id]);
	free_private_names(n);
}

void	private_sems_init(t_philo *p, t_psems_name *n)
{
	n->last_eat_sem_name = sem_lasteat_name(p->id);
	n->eat_counter_sem_name = sem_eatcount_name(p->id);
	if (!n->last_eat_sem_name || !n->eat_counter_sem_name)
		exit((free_private_names(n), p_error(5, p), sem_post(p->death),
				clean_philo(p), 1));
	if ((sem_unlink(n->last_eat_sem_name) == -1
			|| sem_unlink(n->eat_counter_sem_name) == -1) && errno == EACCES)
		exit((free_private_names(n), p_error(6, p), sem_post(p->death),
				clean_philo(p), 1));
	p->last_teat[p->id] = sem_open(n->last_eat_sem_name, O_CREAT, 0644, 1);
	p->eat_counter[p->id] = sem_open(n->eat_counter_sem_name, O_CREAT, 0644, 1);
	if (p->last_teat[p->id] == SEM_FAILED
		|| p->eat_counter[p->id] == SEM_FAILED)
		exit((private_sems_dest(p, n), p_error(7, p), sem_post(p->death),
				clean_philo(p), 1));
	sem_unlink(n->last_eat_sem_name);
	sem_unlink(n->eat_counter_sem_name);
}
