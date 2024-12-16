/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:02:50 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/16 10:18:49 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	*one_philo(t_philo *p)
{
	printf(FORK, (get_time() - p->table->time_start), p->id);
	ft_usleep(get_time() + p->table->t_t_die, p);
	printf("%lu %u is dead\n", (get_time() - p->table->time_start), p->id);
	return (NULL);
}

void	mutex_fork2(t_philo *p)
{
	pthread_mutex_lock(p->forkr);
	pthread_mutex_lock(&p->table->lock);
	if (p->table->end == 0)
		printf(FORK, (get_time() - p->table->time_start), p->id);
	pthread_mutex_unlock(&p->table->lock);
	pthread_mutex_lock(&p->forkl);
	pthread_mutex_lock(&p->table->lock);
	if (p->table->end == 0)
		printf(FORK, (get_time() - p->table->time_start), p->id);
	pthread_mutex_unlock(&p->table->lock);
}

void	mutex_fork_in_order(t_philo *p)
{
	if (&p->forkl < p->forkr)
	{
		pthread_mutex_lock(&p->forkl);
		pthread_mutex_lock(&p->table->lock);
		if (p->table->end == 0)
			printf(FORK, (get_time() - p->table->time_start), p->id);
		pthread_mutex_unlock(&p->table->lock);
		pthread_mutex_lock(p->forkr);
		pthread_mutex_lock(&p->table->lock);
		if (p->table->end == 0)
			printf(FORK, (get_time() - p->table->time_start), p->id);
		pthread_mutex_unlock(&p->table->lock);
	}
	else
		mutex_fork2(p);
}

void	philo_eating_sleeping(t_philo *p)
{
	mutex_fork_in_order(p);
	pthread_mutex_lock(&p->table->lock);
	if (p->table->end == 0)
		printf(EAT, (get_time() - p->table->time_start), p->id);
	p->last_eat = get_time();
	p->eaten++;
	pthread_mutex_unlock(&p->table->lock);
	ft_usleep(p->table->t_eat + get_time(), p);
	pthread_mutex_unlock(p->forkr);
	pthread_mutex_unlock(&p->forkl);
	pthread_mutex_lock(&p->table->lock);
	if (p->table->end == 0)
		printf(SLEEP, (get_time() - p->table->time_start), p->id);
	pthread_mutex_unlock(&p->table->lock);
	ft_usleep((p->table->t_sleep) + get_time(), p);
}

void	*life_style(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	if (p->table->n_philo == 1)
		return (one_philo(p));
	if (p->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&p->table->lock);
		if (p->table->end == 1)
		{
			pthread_mutex_unlock(&p->table->lock);
			break ;
		}
		pthread_mutex_unlock(&p->table->lock);
		philo_eating_sleeping(p);
		pthread_mutex_lock(&p->table->lock);
		if (p->table->end == 0)
		{
			printf(THINK, (get_time() - p->table->time_start), p->id);
		}
		pthread_mutex_unlock(&p->table->lock);
	}
	return (NULL);
}
