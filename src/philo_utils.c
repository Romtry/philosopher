/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:46:58 by rothiery          #+#    #+#             */
/*   Updated: 2024/10/28 12:14:14 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

unsigned int	ft_abs(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

void	free_max(t_global *global)
{
	if (global->p)
		free(global->p);
}

void	print_error(unsigned int n)
{
	if (n == 0)
		write(1, "wrong args ./philosopher n_of_philo t_to_die t_to_eat t_to_sleep (n_of_t_each_philo_must_eat)\n", 94);
	else if (n == 1)
		write(1, "wrong args args n_of_philo t_to_die t_to_eat t_to_sleep (n_of_t_each_philo_must_eat) must be higher than 0\n", 107);
	exit(1);
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
