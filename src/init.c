/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:40:44 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/09 16:52:57 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	args_to_global(t_global *global, char **argv)
{
	global->table.n_philo = ft_uns_atoi(argv[1]);
	if (global->table.n_philo > 200)
		print_error(2);
	global->table.t_t_die = ft_uns_atoi(argv[2]);
	global->table.t_eat = ft_uns_atoi(argv[3]);
	global->table.t_sleep = ft_uns_atoi(argv[4]);
	if (argv[5])
		global->table.n_must_eat = ft_uns_atoi(argv[5]);
	else
		global->table.n_must_eat = -1;
}

void	struct_init(t_global *global)
{
	unsigned int	i;

	i = 0;
	global->table.f_in_table = global->table.n_philo;
	global->table.time_start = get_time();
	global->table.end = 0;
	pthread_mutex_init(&global->table.lock, NULL);
	while (i < global->table.n_philo)
	{
		pthread_mutex_init(&global->p[i].forkl, NULL);
		global->p[i].id = i + 1;
		global->p[i].eaten = 0;
		global->p[i].table = &global->table;
		global->p[i].last_eat = get_time();
		if (i != global->table.n_philo - 1)
			global->p[i].forkr = &global->p[i + 1].forkl;
		else
			global->p[i].forkr = &global->p[0].forkl;
		i++;
	}
}

void	destroy_mutex(t_global *global)
{
	unsigned int	i;

	i = 0;
	while (i < global->table.n_philo)
	{
		pthread_mutex_destroy(&global->p[i].forkl);
		i++;
	}
	pthread_mutex_destroy(&global->table.lock);
}

void	thread_init(t_global *global)
{
	unsigned long	i;
	pthread_t		death_t;

	struct_init(global);
	i = 0;
	while (i < global->table.n_philo)
	{
		pthread_create(&global->p[i].thread, NULL, &life_style, &global->p[i]);
		i++;
	}
	if (global->table.n_philo > 1)
		pthread_create(&death_t, NULL, &death, global);
	i = 0;
	while (i < global->table.n_philo)
	{
		pthread_join(global->p[i].thread, NULL);
		i++;
	}
	if (global->table.n_philo > 1)
		pthread_join(death_t, NULL);
	destroy_mutex(global);
}
