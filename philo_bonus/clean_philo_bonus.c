/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:10:59 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 14:32:24 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	close_sems(t_philo *p)
{
	sem_close(p->w_death);
	sem_close(p->death);
	sem_close(p->print);
	sem_close(p->start);
	sem_close(p->finish_flg);
	sem_close(p->forks);
	sem_close(p->eat);
}

void	clean_philo(t_philo *p)
{
	close_sems(p);
	free(p->philo);
	free(p->last_teat);
	free(p->eat_counter);
}

void	destroy_philo(t_philo *p)
{
	clean_philo(p);
}

void	unlink_sems_open(t_philo *p)
{
	if ((sem_unlink(SEM_DEATH) == -1 || sem_unlink(SEM_START) == -1
			|| sem_unlink(SEM_PRINT) == -1 || sem_unlink(SEM_FINISH) == -1
			|| sem_unlink(SEM_FORKS) == -1 || sem_unlink(SEM_EAT) == -1
			|| sem_unlink(SEM_WDEATH) == -1) && errno == EACCES)
		exit((clean_philo(p), p_rror(3), 1));
}

void	unlink_sems_close(void)
{
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_START);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FINISH);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_EAT);
	sem_unlink(SEM_WDEATH);
}
