/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:30:36 by rothiery          #+#    #+#             */
/*   Updated: 2024/11/22 13:23:10 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	print_error(unsigned int n)
{
	if (n == 0)
	{
		write(1, "\033[38;5;196mWrong number of args\n", 32);
		exit(1);
	}
	else if (n == 1)
	{
		write(1, "\e[38;5;196mArgs must be higher than 60 exept n_philo\n", 53);
		exit(2);
	}
	else if (n == 2)
	{
		write(1, "\033[38;5;196mNeed less than 200 philo\n", 25);
		exit(3);
	}
}

void	parsing(int argc, char **argv, t_global *global)
{
	if (argc != 5 && argc != 6)
		print_error(0);
	args_to_global(global, argv);
	if (global->table.n_philo == 0 || global->table.t_t_die < 60
		|| global->table.t_eat < 60 || global->table.t_sleep < 60
		|| global->table.n_must_eat == 0)
		print_error(1);
}

int	main(int argc, char **argv)
{
	t_global	global;

	parsing(argc, argv, &global);
	thread_init(&global);
}
