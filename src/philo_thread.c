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
	unsigned long	ret;
	struct timeval	time;

	ret = time.tv_sec * 1000 + time.tv_usec / 1000;
	return(ret);
}

void *life_style(void *arg)
{
	t_liste	*liste;

	liste = (t_liste *)arg;
	liste->p->last_t_eat = 0;
	liste->p->eaten = 0;
	while (liste->p->last_t_eat - liste->time_start < liste->t_t_die
		&& liste->p->eaten < liste->n_must_eat)
	{
		if (liste->p->forkl == 1)
		{
			liste->p->eaten++;
			pthread_mutex_lock(&liste->lock);
			liste->f_in_table++;
			pthread_mutex_unlock(&liste->lock);
			liste->p->last_t_eat = get_time();
			usleep(liste->t_sleep);
		}
		else
		{
			liste->p->forkl = 1;
			pthread_mutex_lock(&liste->lock);
			liste->f_in_table--;
			pthread_mutex_unlock(&liste->lock);
		}
	}
	(void)liste;
	return (NULL);
}

void philo_init(t_liste *liste)
{
	unsigned long i;

	i = 0;
	liste->p = malloc(sizeof(struct s_philo) * liste->n_philo);
	liste->f_in_table = liste->n_philo;
	while (i < liste->n_philo)
	{
		liste->p[i].id = i + 1;
		pthread_create(&liste->p[i].thread, NULL, &life_style, &liste);
		i++;
	}
	liste->time_start = get_time();
	i = 0;
	while (i < liste->n_philo)
	{
		pthread_join(liste->p[i].thread, NULL);
		i++;
	}
}
