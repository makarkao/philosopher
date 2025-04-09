/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:48:40 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 13:06:00 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_pargs	*init_pargs(char **av, int ac, pthread_mutex_t *fork)
{
	t_pargs	*pargs;

	pargs = malloc(sizeof(t_pargs));
	if (!pargs)
		return (p_rror(1), NULL);
	(1) && (pargs->phi_n = ft_atoi(av[1]), pargs->phi_d = ft_atoi(av[2]));
	(1) && (pargs->phi_e = ft_atoi(av[3]), pargs->phi_s = ft_atoi(av[4]));
	if (ac == 6)
		pargs->phi_ne = ft_atoi(av[5]);
	else
		pargs->phi_ne = -1;
	(1) && (pargs->phi_t = 0, pargs->death_flag = 0, pargs->current = 0);
	if (pargs->phi_n % 2 == 1)
	{
		if (pargs->phi_e > pargs->phi_s)
			pargs->phi_t = pargs->phi_e;
		else if (pargs->phi_e == pargs->phi_s)
			pargs->phi_t = pargs->phi_e / 2;
	}
	if (pthread_mutex_init((&(pargs->prt_lock)), NULL))
		return (free(pargs), p_rror(2), NULL);
	if (pthread_mutex_init((&(pargs->lock_df)), NULL))
		return (pthread_mutex_destroy(&(pargs->prt_lock)), free(pargs),
			p_rror(2), NULL);
	return (pargs->fork = fork, pargs);
}

static t_phi	*init_phi_i(int i, int n, t_pargs *args)
{
	t_phi	*phi;

	phi = malloc(sizeof(t_phi));
	if (!phi)
		return (p_rror(1), NULL);
	(1) && (phi->index = i + 1, phi->n_eat = 0);
	if (pthread_mutex_init((&(phi->n_eat_mtx)), NULL))
		return (free(phi), p_rror(2), NULL);
	if (pthread_mutex_init((&(phi->lt_eat_mtx)), NULL))
		return (pthread_mutex_destroy(&(phi->n_eat_mtx)), free(phi), p_rror(2),
			NULL);
	if (n == 1)
		return (phi->fork_1 = &args->fork[i], phi);
	if (i % 2 == 0 && i != n - 1)
	{
		phi->fork_1 = &args->fork[i];
		phi->fork_2 = &args->fork[(n + i - 1) % n];
	}
	else
	{
		phi->fork_1 = &args->fork[i - 1];
		phi->fork_2 = &args->fork[i];
	}
	return (phi);
}

static t_philo	**init_philo_elems(t_philo **p, t_pargs *args)
{
	int	i;
	int	n;

	i = 0;
	n = args->phi_n;
	while (i < n)
	{
		p[i] = malloc(sizeof(t_philo));
		if (!p[i])
			return (destroy_shmutexes(p), free(args->fork), free(args),
				free_philo(p, i), free(p), p_rror(1), NULL);
		p[i]->pargs = args;
		p[i]->phi = init_phi_i(i, n, args);
		if (!p[i]->phi)
			return (destroy_shmutexes(p), destroy_pmutexes(p, i),
				free(args->fork), free(args), free_philo(p, i), free(p[i]),
				free(p), NULL);
		i++;
	}
	return (p);
}

t_philo	**init_philo(t_philo **p, char **av, int ac)
{
	int				n;
	int				i;
	pthread_mutex_t	*fork;
	t_pargs			*args;

	n = ft_atoi(av[1]);
	if (n < 1)
		return (NULL);
	fork = malloc(sizeof(pthread_mutex_t) * n);
	if (!fork)
		return (p_rror(1), NULL);
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&fork[i], NULL))
			return (destroy_fork(p, i), free(fork), p_rror(2), NULL);
		i++;
	}
	args = init_pargs(av, ac, fork);
	if (!args)
		return (destroy_fork(p, n), free(fork), NULL);
	p = malloc(sizeof(t_philo *) * n);
	if (!p)
		return (destroy_shmutexes(p), free(fork), free(args), p_rror(1), NULL);
	return (init_philo_elems(p, args));
}
