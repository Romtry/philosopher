/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:02:50 by rothiery          #+#    #+#             */
/*   Updated: 2024/11/21 15:44:42 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

unsigned int	one_philo(t_philo *p)
{
	pthread_mutex_lock(&p->table->lock);
	if (p->table->n_philo == 1)
	{
		printf(FORK, (get_time() - p->table->time_start), p->id);
		ft_usleep(get_time() + p->table->t_t_die, p);
		printf("%lu %u is dead\n", (get_time() - p->table->time_start), p->id);
		pthread_mutex_unlock(&p->table->lock);
		return (1);
	}
	pthread_mutex_unlock(&p->table->lock);
	return (0);
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
	pthread_mutex_lock(&p->table->lock);
	if (p->table->end == 0)
	{
		printf(FORK, (get_time() - p->table->time_start), p->id);
		printf(FORK, (get_time() - p->table->time_start), p->id);
		printf(EAT, (get_time() - p->table->time_start), p->id);
	}
	p->last_eat = get_time();
	p->eaten++;
	pthread_mutex_unlock(&p->table->lock);
	ft_usleep(p->table->t_eat + get_time(), p);
	pthread_mutex_unlock(&p->forkl);
	pthread_mutex_unlock(p->forkr);
}

void	philo_sleeping(t_philo *p)
{
	pthread_mutex_lock(&p->table->lock);
	if (p->table->end == 0)
	{
		printf(SLEEP, (get_time() - p->table->time_start), p->id);
	}
	pthread_mutex_unlock(&p->table->lock);
	ft_usleep((p->table->t_sleep) + get_time(), p);
}

void	*life_style(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	if (one_philo(p) == 1)
		return (NULL);
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
		else
			printf(THINK, (get_time() - p->table->time_start), p->id);
		pthread_mutex_unlock(&p->table->lock);
		philo_eating(p);
		philo_sleeping(p);
	}
	return (NULL);
}
