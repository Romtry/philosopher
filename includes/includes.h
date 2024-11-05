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
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include "ft_printf.h"

typedef struct s_table
{
	unsigned int	n_philo;
	unsigned int	t_t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	n_must_eat;
	unsigned int	f_in_table;
	unsigned long	time_start;
	pthread_mutex_t	lock;
} t_table;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	unsigned int	last_t_eat;
	pthread_mutex_t	forkl;
	pthread_mutex_t	*forkr;
	unsigned int	eaten;
	struct s_table	table;
} t_philo;

typedef struct s_global
{
	struct s_philo	*p;
	struct s_table	table;
} t_global;

unsigned int	ft_abs(int n);
void	free_max(t_global *global);
void	print_error(unsigned int n);
int		ft_uns_atoi(const char *nptr);
void	philo_init(t_global *global);

#endif
