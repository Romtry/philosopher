/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:51:37 by rothiery          #+#    #+#             */
/*   Updated: 2024/11/19 11:59:19 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

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
	unsigned int	is_dead;
	unsigned int	id;
	unsigned long	last_eat;
	pthread_mutex_t	forkl;
	pthread_mutex_t	*forkr;
	unsigned int	eaten;
	struct s_table	table;
} t_philo;

typedef struct s_global
{
	struct s_philo	p[200];
	struct s_table	table;
} t_global;

unsigned int	ft_abs(int n);
void			free_max(t_global *global);
void			print_error(unsigned int n);
int				ft_uns_atoi(const char *nptr);
void			thread_init(t_global *global);
void			ft_usleep(unsigned long n);
unsigned long	get_time(void);
void			*death(void *ptr);
void 			*life_style(void *ptr);
int				end(t_philo *p);
void			args_to_global(t_global *global, char **argv);

#endif
