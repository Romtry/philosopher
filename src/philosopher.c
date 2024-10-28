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

void liste_init(t_liste *liste, char **argv)
{
	liste->n_philo = ft_uns_atoi(argv[1]);
	liste->t_t_die = ft_uns_atoi(argv[2]);
	liste->t_eat = ft_uns_atoi(argv[3]);
	liste->t_sleep = ft_uns_atoi(argv[4]);
	liste->n_m_eat = ft_uns_atoi(argv[5]);
	// liste->p.fork = malloc(sizeof(unsigned int) * (liste->n_philo + 1));
	// liste->p.fork[0] = liste->n_philo;
	// liste->p.eaten = 0;
}

void parsing(int argc, char **argv, t_liste *liste)
{
	if (argc != 5 && argc != 6)
		print_error(0);
	liste_init(liste, argv);
	if (liste->n_philo == 0 || liste->t_t_die == 0 || liste->t_eat == 0 ||
		liste->t_sleep == 0 || liste->n_m_eat == 0)
		print_error(1);
}

int main(int argc, char **argv)
{
	t_liste liste;

	parsing(argc, argv, &liste);
	write(1, "input ok !\n", 11);
	printf("%d, %d, %d, %d, %d\n", liste.n_philo, liste.t_t_die, liste.t_eat, liste.t_sleep, liste.n_m_eat);
	philo_init(&liste);
	free_max(&liste);
}
