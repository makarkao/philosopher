/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:26:15 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/26 21:49:23 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	p_rror(int n)
{
	if (n == 0)
		printf("invalid arguments\n");
	if (n == 1)
		printf("malloc error: during initialization\n");
	else if (n == 2)
		printf("sem_open error: during initialization\n");
	else if (n == 3)
		printf("sem_close at open error: during initialization\n");
}

void	p_error(int n, t_philo *p)
{
	sem_wait(p->print);
	if (n == 0)
		printf("fork error: child creation failed\n");
	else if (n == 1)
		printf("pthread_create error: killer thread ceation\n");
	else if (n == 2)
		printf("pthread_join error: killer thread join\n");
	else if (n == 3)
		printf("pthread_create error: die thread ceation\n");
	else if (n == 4)
		printf("pthread_join error: die thread join\n");
	else if (n == 5)
		printf("malloc error: in private sem names\n");
	else if (n == 6)
		printf("sem_close at open error: in private sem names\n");
	else if (n == 7)
		printf("sem_open error: in private sem names\n");
	else if (n == 8)
		printf("waitpid error: in philo bonus\n");
	sem_post(p->print);
}
