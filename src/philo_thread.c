/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:02:50 by rothiery          #+#    #+#             */
/*   Updated: 2024/11/19 13:59:13 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	one_philo(t_philo *p)
{
	pthread_mutex_lock(&p->table.lock);
	if (p->table.n_philo == 1)
	{
		printf("%lu %u has taken a fork\n", (get_time() - p->table.time_start), p->id);
		ft_usleep(p->table.t_t_die);
		pthread_mutex_unlock(&p->table.lock);
		end(p);
	}
	pthread_mutex_unlock(&p->table.lock);
}

void	mutex_fork_in_order(t_philo *p)
{
	if (&p->forkl < p->forkr)
	{
		pthread_mutex_lock(&p->forkl);
		pthread_mutex_lock(p->forkr);
	}
	else
	{
		pthread_mutex_lock(p->forkr);
		pthread_mutex_lock(&p->forkl);
	}
}

void	philo_eating(t_philo *p)
{
	mutex_fork_in_order(p);
	printf("%lu %u has taken a fork\n", (get_time() - p->table.time_start), p->id);
	printf("%lu %u has taken a fork\n", (get_time() - p->table.time_start), p->id);
	printf("%lu %u is eating\n", (get_time() - p->table.time_start), p->id);
	ft_usleep(p->table.t_eat + get_time());
	p->eaten++;
	p->last_eat = get_time();
	pthread_mutex_unlock(&p->forkl);
	pthread_mutex_unlock(p->forkr);
}

void	philo_sleeping(t_philo *p)
{
	printf("%lu %u is sleeping\n", (get_time() - p->table.time_start), p->id);
	ft_usleep((p->table.t_sleep) + get_time());
}

void	*life_style(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	one_philo(p);
	if(p->id % 2 == 0)
		ft_usleep((p->table.t_eat) + get_time());
	while(1)
	{
		philo_eating(p);
		if (end(p) == 1)
			break;
		philo_sleeping(p);
		if (end(p) == 1)
			break;
		printf("%lu %u is thinking\n", (get_time() - p->table.time_start), p->id);
		if (end(p) == 1)
			break;
	}
	return (NULL);
}
