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

void *life_style(void *arg)
{
	t_liste	*liste;

	liste = (t_liste *)arg;
	pthread_mutex_lock(&fork);
	
	pthread_mutex_unlock(&fork);
	(void)liste;
	return (NULL);
}

void philo_init(t_liste *liste)
{
	unsigned long i;

	i = 0;
	liste->p = malloc(sizeof(struct s_philo) * liste->n_philo);

	pthread_mutex_init(&lock, NULL);

	while (i < liste->n_philo)
	{
		liste->p[i].id = i + 1;
		pthread_create(&liste->p[i].thread, NULL, &life_style, &liste);
		i++;
	}
	i = 0;
	while (i < liste->n_philo)
	{
		pthread_join(liste->p[i].thread, NULL);
		i++;
	}
}
