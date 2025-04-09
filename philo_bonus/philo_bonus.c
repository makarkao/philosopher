/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:14:38 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 14:51:06 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	args_check(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_numeric(av[i]) || !av[i][0])
			exit((p_rror(0), 1));
		i++;
	}
}

static void	post_philo(t_philo *p)
{
	int (i), (status), (exit_s);
	(1) && (i = 0, exit_s = 0);
	while (i < p->phi_n)
	{
		if (waitpid(-1, &status, 0) == -1)
			(p_error(8, p), sem_post(p->death), exit_s = 1);
		sem_wait(p->finish_flg);
		if (WIFSIGNALED(status) && p->finish_falg == 0)
			(p_error(8, p), sem_post(p->death), exit_s = 1);
		sem_post(p->finish_flg);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			exit_s = 1;
		i++;
	}
	sem_wait(p->finish_flg);
	p->finish_falg = 1;
	sem_post(p->finish_flg);
	sem_post(p->death);
	if (pthread_join(p->killer, NULL))
		exit((p_error(2, p), destroy_philo(p), 1));
	destroy_philo(p);
	exit(exit_s);
}

int	main(int ac, char **av)
{
	t_philo	p;

	if (ac != 5 && ac != 6)
		return (1);
	args_check(ac, av);
	init_philo(&p, ac, av);
	p.current = get_time_ms();
	while (p.id < p.phi_n)
	{
		p.philo[p.id] = fork();
		if (p.philo[p.id] == -1)
		{
			(p_error(0, &p), sem_post(p.death));
			break ;
		}
		else if (p.philo[p.id] == 0)
			philo_handler(&p);
		p.id++;
	}
	if (pthread_create(&p.killer, NULL, kill_handler, &p))
		exit((p_error(1, &p), destroy_philo(&p), 1));
	post_philo(&p);
	return (0);
}
