/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:14:02 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 14:36:03 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	init_sems(t_philo *p)
{
	p->philo = malloc(sizeof(pid_t) * p->phi_n);
	if (!p->philo)
		exit((p_rror(1), 1));
	p->last_teat = malloc(sizeof(sem_t *) * p->phi_n);
	if (!p->last_teat)
		exit((free(p->philo), p_rror(1), 1));
	p->eat_counter = malloc(sizeof(sem_t *) * p->phi_n);
	if (!p->eat_counter)
		exit((free(p->philo), free(p->eat_counter), p_rror(1), 1));
	unlink_sems_open(p);
	p->death = sem_open(SEM_DEATH, O_CREAT, 0644, 0);
	p->start = sem_open(SEM_START, O_CREAT, 0644, 0);
	p->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	p->finish_flg = sem_open(SEM_FINISH, O_CREAT, 0644, 1);
	p->forks = sem_open(SEM_FORKS, O_CREAT, 0644, p->phi_n);
	p->eat = sem_open(SEM_EAT, O_CREAT, 0644, p->phi_n / 2);
	p->w_death = sem_open(SEM_WDEATH, O_CREAT, 0644, 1);
	if (p->death == SEM_FAILED || p->start == SEM_FAILED
		|| p->print == SEM_FAILED || p->finish_flg == SEM_FAILED
		|| p->forks == SEM_FAILED || p->eat == SEM_FAILED
		|| p->w_death == SEM_FAILED)
		exit((destroy_philo(p), p_rror(2), 1));
	unlink_sems_close();
}

void	init_philo(t_philo *p, int ac, char **av)
{
	p->phi_n = ft_atoi(av[1]);
	p->phi_d = ft_atoi(av[2]);
	p->phi_e = ft_atoi(av[3]);
	p->phi_s = ft_atoi(av[4]);
	if (ac == 6)
	{
		p->phi_ne = ft_atoi(av[5]);
		p->phine_flag = 1;
	}
	else
	{
		p->phi_ne = -1;
		p->phine_flag = 0;
	}
	p->t_phi = 0;
	if (p->phi_n % 2 == 1)
	{
		if (p->phi_e > p->phi_s)
			p->t_phi = p->phi_e;
		else if (p->phi_e == p->phi_s)
			p->t_phi = p->phi_e / 2;
	}
	(1) && (p->id = 0, p->n_eat = 0, p->finish_falg = 0);
	init_sems(p);
}

char	*sem_lasteat_name(int n)
{
	char	*id;
	char	*str;

	id = ft_itoa(n);
	str = ft_strjoin("/last_eat_sem_", id);
	free(id);
	return (str);
}

char	*sem_eatcount_name(int n)
{
	char	*id;
	char	*str;

	id = ft_itoa(n);
	str = ft_strjoin("/count_eat_sem_", id);
	free(id);
	return (str);
}
