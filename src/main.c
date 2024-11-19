/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:30:36 by rothiery          #+#    #+#             */
/*   Updated: 2024/11/19 11:53:08 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void parsing(int argc, char **argv, t_global *global)
{
	if (argc != 5 && argc != 6)
		print_error(0);
	args_to_global(global, argv);
	if (global->table.n_philo == 0 || global->table.t_t_die == 0 || global->table.t_eat == 0 ||
		global->table.t_sleep == 0 || global->table.n_must_eat == 0)
		print_error(1);
}

int main(int argc, char **argv)
{
	t_global global;

	parsing(argc, argv, &global);
	thread_init(&global);
}