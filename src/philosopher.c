/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:30:36 by rothiery          #+#    #+#             */
/*   Updated: 2024/10/28 12:14:41 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void global_init(t_global *global, char **argv)
{
	global->table.n_philo = ft_uns_atoi(argv[1]);
	global->table.t_t_die = ft_uns_atoi(argv[2]);
	global->table.t_eat = ft_uns_atoi(argv[3]);
	global->table.t_sleep = ft_uns_atoi(argv[4]);
	if (argv[5])
		global->table.n_must_eat = ft_uns_atoi(argv[5]);
}

void parsing(int argc, char **argv, t_global *global)
{
	if (argc != 5 && argc != 6)
		print_error(0);
	global_init(global, argv);
	if (global->table.n_philo == 0 || global->table.t_t_die == 0 || global->table.t_eat == 0 ||
		global->table.t_sleep == 0 || global->table.n_must_eat == 0)
		print_error(1);
}

int main(int argc, char **argv)
{
	t_global global;

	parsing(argc, argv, &global);
	// write(1, "input ok !\n", 11);
	// ft_printf("%d, %d, %d, %d, %d\n", global.table.n_philo, global.table.t_t_die, global.table.t_eat, global.table.t_sleep, global.table.n_must_eat);
	philo_init(&global);
	free_max(&global);
}
