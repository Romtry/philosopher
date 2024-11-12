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

int	end(t_philo *p)
{
	if 	 (get_time() - p->last_eat > p->table.t_t_die
		|| p->eaten > p->table.n_must_eat || p->is_dead != 0)
	{
		if (p->eaten >= p->table.t_eat)
			printf("%lu %u has eaten %u times", (get_time() - p->table.time_start), p->id, p->table.t_eat);
		else
			printf("%lu %u is dead\n", (get_time() - p->table.time_start), p->id);
		return(1);
	}
	return(0);
}

void *life_style(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	p->last_eat = p->table.time_start;
	p->eaten = 0;
	if (p->table.n_philo == 1)
	{
		printf("%lu %u has taken a fork\n", (get_time() - p->table.time_start), p->id);
		ft_usleep(p->table.t_t_die);
		end(p);
	}
	if(p->id % 2 == 0)
		ft_usleep((p->table.t_eat) + get_time());
	while(1)
	{
		pthread_mutex_lock(&p->forkl);
		printf("%lu %u has taken a fork\n", (get_time() - p->table.time_start), p->id);
		pthread_mutex_lock(p->forkr);
		printf("%lu %u has taken a fork\n", (get_time() - p->table.time_start), p->id);
		printf("%lu %u is eating\n", (get_time() - p->table.time_start), p->id);
		ft_usleep(p->table.t_eat + get_time());
		p->eaten++;
		p->last_eat = get_time();
		pthread_mutex_unlock(&p->forkl);
		pthread_mutex_unlock(p->forkr);
		if (end(p) == 1)
			break;
		printf("%lu %u is sleeping\n", (get_time() - p->table.time_start), p->id);
		ft_usleep((p->table.t_sleep) + get_time());
		if (end(p) == 1)
			break;
		printf("%lu %u is thinking\n", (get_time() - p->table.time_start), p->id);
		ft_usleep(ft_abs(p->table.t_eat - p->table.t_sleep) + get_time());
		if (end(p) == 1)
			break;
	}
	return (NULL);
}

void	*death(void *ptr)
{
	unsigned int	i;
	t_global	*global;

	global = (t_global *)ptr;
	i = 0;
	while(1)
	{
		if (i == global->table.n_philo)
			i = 0;
		if (global->p[i].is_dead == 1)
			break;
		i++;
	}
	i = 0;
	while (i < global->table.n_philo)
	{
		global->p[i].is_dead = 1;
		i++;
	}
	return (NULL);
}

void philo_init(t_global *global)
{
	unsigned long	i;
	pthread_t		death_t;

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
	pthread_create(&death_t, NULL, &death, &global);
	pthread_join(death_t, NULL);
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
