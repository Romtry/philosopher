/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:51:37 by rothiery          #+#    #+#             */
/*   Updated: 2024/10/28 14:14:45 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	unsigned int	last_t_eat;
	unsigned int	forkl;
	unsigned int	forkr;
	unsigned int	eaten;
};

typedef struct s_liste
{
	unsigned int	n_philo;
	unsigned int	t_t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	n_must_eat;
	unsigned int	f_in_table;
	unsigned int	time_start;
	pthread_mutex_t	lock;
	struct s_philo	*p;
} t_liste;

void	free_max(t_liste *liste);
void	print_error(unsigned int n);
int		ft_uns_atoi(const char *nptr);
void	philo_init(t_liste *liste);

#endif
