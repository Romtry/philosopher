/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:02:50 by rothiery          #+#    #+#             */
/*   Updated: 2024/10/28 14:16:50 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

unsigned int	bite;

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	sec;
	unsigned long	nano;

	gettimeofday(&time, NULL);
	sec = time.tv_sec;
	nano = time.tv_usec;
	// ft_printf("sec = %lu, nano = %lu, ", sec * 1000, nano / 1000);
	return((sec * 1000) + (nano / 1000));
}

void	ft_usleep(unsigned long n)
{
	unsigned long	i;

	i = 0;
	while(n > get_time())
	{
		// ft_printf("%lu, %lu\n", n, get_time());
		usleep(50);
		if (i == 10)
			exit(1);
	}
}

void *life_style(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	p->last_t_eat = 0;
	p->eaten = 0;
	if(p->id % 2 == 0)
		ft_usleep((p->table.t_eat * 1000) + get_time());
	//  (p->last_t_eat - p->table.time_start < p->table.t_t_die
	// 	&& p->eaten < p->table.n_must_eat)
	while(1)
	{
		pthread_mutex_lock(&p->forkl);
		printf("%lu %u has taken a fork\n", (get_time() - p->table.time_start), p->id);
		pthread_mutex_lock(p->forkr);
		printf("%lu %u has taken a fork\n", (get_time() - p->table.time_start), p->id);
		printf("%lu %u is eating\n", (get_time() - p->table.time_start), p->id);
		ft_usleep(p->table.t_eat + get_time());
		p->eaten++;
		printf("%lu %u is sleeping\n", (get_time() - p->table.time_start), p->id);
		ft_usleep((p->table.t_sleep) + get_time());
		printf("%lu %u is thinking\n", (get_time() - p->table.time_start), p->id);
		ft_usleep(ft_abs(p->table.t_eat - p->table.t_sleep) + get_time());
		pthread_mutex_unlock(&p->forkl);
		pthread_mutex_unlock(p->forkr);
	}
	return (NULL);
}

void philo_init(t_global *global)
{
	unsigned long i;

	i = 0;
	global->p = malloc(sizeof(struct s_philo) * global->table.n_philo);
	global->table.f_in_table = global->table.n_philo;
	global->table.time_start = get_time();
	pthread_mutex_init(&global->table.lock, NULL);
	while (i < global->table.n_philo)
	{
		pthread_mutex_init(&global->p[i].forkl, NULL);
		global->p[i].id = i + 1;
		global->p[i].table = global->table;
		if (i != global->table.n_philo - 1)
			global->p[i].forkr = &global->p[i + 1].forkl;
		else
			global->p[i].forkr = &global->p[0].forkl;
		i++;
	}
	i = 0;
	while (i < global->table.n_philo)
	{
		pthread_create(&global->p[i].thread, NULL, &life_style, &global->p[i]);
		i++;
	}
	i = 0;
	while (i < global->table.n_philo)
	{
		pthread_join(global->p[i].thread, NULL);
		i++;
	}
}
