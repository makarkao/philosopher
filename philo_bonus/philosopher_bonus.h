/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:30:42 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/31 14:37:26 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <limits.h>

# define SEM_DEATH "/death_sem"
# define SEM_START "/start_sem"
# define SEM_PRINT "/print_sem"
# define SEM_FINISH "finish_flg_sem"
# define SEM_FORKS "/forks_sem"
# define SEM_EAT "/eat_sem"
# define SEM_WDEATH "/wdeath_sem"

typedef struct philo_s
{
	int				phi_n;
	unsigned long	phi_d;
	int				phi_e;
	int				phi_s;
	int				phi_ne;
	int				t_phi;
	int				id;
	int				n_eat;
	int				phine_flag;
	int				finish_falg;
	unsigned long	last_time_eat;
	unsigned long	current;
	pthread_t		killer;
	pid_t			*philo;
	sem_t			**last_teat;
	sem_t			**eat_counter;
	sem_t			*eat;
	sem_t			*forks;
	sem_t			*death;
	sem_t			*w_death;
	sem_t			*finish_flg;
	sem_t			*print;
	sem_t			*start;
}					t_philo;

typedef struct psems_name_s
{
	char			*last_eat_sem_name;
	char			*eat_counter_sem_name;
}					t_psems_name;

int					ft_atoi(const char *str);
int					is_numeric(char *s);
void				clean_philo(t_philo *p);
void				init_philo(t_philo *p, int ac, char **av);
char				*sem_lasteat_name(int n);
char				*sem_eatcount_name(int n);
void				*kill_handler(void *t);
void				*death_handler(void *t);
void				philo_handler(t_philo *p);
char				*ft_itoa(int x);
char				*ft_strjoin(char *s1, char *s2);
void				unlink_sems_open(t_philo *p);
void				unlink_sems_close(void);
unsigned long		get_time_ms(void);
unsigned long		time_pass_ms(unsigned long current);
void				destroy_philo(t_philo *p);
void				private_sems_dest(t_philo *p, t_psems_name *n);
void				private_sems_init(t_philo *p, t_psems_name *n);
void				p_rror(int n);
void				p_error(int n, t_philo *p);

#endif