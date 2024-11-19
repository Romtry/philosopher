/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:44:10 by rothiery          #+#    #+#             */
/*   Updated: 2024/11/19 13:12:53 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	end(t_philo *p)
{
	pthread_mutex_lock(&p->table.lock);
	if 	 (get_time() - p->last_eat > p->table.t_t_die && p->is_dead == 0)
	{
		p->is_dead = 1;
		printf("%lu %u is dead\n", (get_time() - p->table.time_start), p->id);
	}
	if (p->is_dead != 0)
	{
		pthread_mutex_unlock(&p->table.lock);
		return(1);
	}
	pthread_mutex_unlock(&p->table.lock);
	return(0);
}

void	legalise_nuclear_bomb(t_global *global)
{
	unsigned int	i;

	i = 0;
	while (i < global->table.n_philo)
	{
		global->p[i].is_dead = 1;
		i++;
	}
	pthread_mutex_unlock(&global->table.lock);
}

unsigned int	have_eat(t_global *global)
{
	unsigned int	i;

	i = 0;
	while(global->p[i].eaten == 1 && i <= global->table.n_philo)
		i++;
	if (i == global->table.n_philo)
	{
		legalise_nuclear_bomb(global);
		return(0);
	}
	return (1);
}

void	*death(void *ptr)
{
	unsigned int	i;
	t_global	*global;

	global = (t_global *)ptr;
	i = 0;
	while(1)
	{
		pthread_mutex_lock(&global->table.lock);
		if (i > global->table.n_philo)
			i = 0;
		if (global->p[i].is_dead == 1)
		{
			legalise_nuclear_bomb(global);
			break;
		}
		else if (have_eat(global) == 0)
			break;
		pthread_mutex_unlock(&global->table.lock);
		i++;
	}
	return (NULL);
}
