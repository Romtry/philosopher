/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:46:58 by rothiery          #+#    #+#             */
/*   Updated: 2024/11/21 15:52:18 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

unsigned int	ft_abs(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

static int	atoirep(const char *nptr, int i)
{
	unsigned int	rep;

	rep = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		rep = (rep * 10) + (nptr[i] - 48);
		i++;
	}
	return (rep);
}

int	ft_uns_atoi(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
		print_error(1);
	else if (nptr[i] == '+')
		i++;
	if (nptr[i] < '0' || nptr[i] > '9')
		return (0);
	else
		return (atoirep(nptr, i));
}

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	sec;
	unsigned long	nano;

	gettimeofday(&time, NULL);
	sec = time.tv_sec;
	nano = time.tv_usec;
	return ((sec * 1000) + (nano / 1000));
}

void	ft_usleep(unsigned long n, t_philo *p)
{
	while (n > get_time())
	{
		pthread_mutex_lock(&p->table->lock);
		if (p->table->end == 1)
		{
			pthread_mutex_unlock(&p->table->lock);
			return ;
		}
		pthread_mutex_unlock(&p->table->lock);
		usleep(50);
	}
}
