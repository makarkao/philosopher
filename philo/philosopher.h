/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:19:42 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 13:37:56 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct pargs_s
{
	int				phi_n;
	unsigned long	phi_d;
	unsigned long	phi_e;
	unsigned long	phi_s;
	unsigned long	phi_t;
	int				phi_ne;
	int				death_flag;
	unsigned long	current;
	pthread_mutex_t	prt_lock;
	pthread_mutex_t	lock_df;
	pthread_mutex_t	*fork;
}					t_pargs;

typedef struct phi_s
{
	pthread_t		philo;
	pthread_t		death;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	pthread_mutex_t	lt_eat_mtx;
	pthread_mutex_t	n_eat_mtx;
	unsigned long	last_time_eat;
	int				index;
	int				n_eat;
}					t_phi;

typedef struct philo_s
{
	t_pargs			*pargs;
	t_phi			*phi;
}					t_philo;

void				clean_philo(t_philo **p);
long long			ft_atoi(const char *str);
int					is_numeric(char *s);
void				*philo_est_handler(void *t);
void				*philo_death_handler(void *t);
unsigned long		timepass(unsigned long current);
unsigned long		get_time_ms(void);
t_philo				**init_philo(t_philo **p, char **av, int ac);
int					manage_threads(t_philo **p);
void				destroy_fork(t_philo **p, int n);
void				t_psems_name(t_philo **p);
void				destroy_pmutexes(t_philo **p, int n);
void				destroy_shmutexes(t_philo **p);
void				destroy_mutexes(t_philo **p);
void				unlock_forks(t_philo *p, int mask);
void				p_rror(int n);
void				free_philo(t_philo **p, int n);
void				p_error(int n, t_philo *p);
int					print_state(int state, int mask, t_philo *p);

#endif