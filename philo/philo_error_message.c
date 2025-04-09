/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:40:39 by makarkao          #+#    #+#             */
/*   Updated: 2025/03/26 21:41:57 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	p_rror(int n)
{
	if (n == 0)
		printf("Invalid input\n");
	if (n == 1)
		printf("malloc error: during initialization\n");
	else if (n == 2)
		printf("mutex_init error: during initialization\n");
}

void	p_error(int n, t_philo *p)
{
	pthread_mutex_lock(&(p->pargs->prt_lock));
	if (n == 3)
		printf("pthread_create error: during thread management\n");
	else if (n == 4)
		printf("pthread_join error: during thread management\n");
	pthread_mutex_unlock(&(p->pargs->prt_lock));
}
