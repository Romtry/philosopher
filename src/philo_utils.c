/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:46:58 by rothiery          #+#    #+#             */
/*   Updated: 2024/10/10 14:58:20 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	print_error(unsigned int n)
{
	if (n == 0)
		write(1, "wrong args ./philosopher n_of_philo t_to_die t_to_eat t_to_sleep n_of_t_each_philo_must_eat\n", 128);
	exit(1);
}
