/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:44:10 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/09 09:44:49 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

unsigned int	ate(t_global *global)
{
	unsigned int	i;

	i = 0;
	while (global->p[i].eaten >= global->table.n_must_eat
		&& i < global->table.n_philo)
		i++;
	if (i == global->table.n_philo)
	{
		global->table.end = 1;
		pthread_mutex_unlock(&global->table.lock);
		return (0);
	}
	return (1);
}

void	*death(void *ptr)
{
	unsigned int	i;
	t_global		*global;

	global = (t_global *)ptr;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&global->table.lock);
		while (i < global->table.n_philo)
		{
			if (get_time() - global->p[i].last_eat > global->table.t_t_die)
			{
				global->table.end = 1;
				printf(DEAD, (get_time() - global->table.time_start), i + 1);
				pthread_mutex_unlock(&global->table.lock);
				return (NULL);
			}
			i++;
		}
		if (ate(global) == 0)
			return (NULL);
		pthread_mutex_unlock(&global->table.lock);
		usleep(100);
	}
	return (NULL);
}
